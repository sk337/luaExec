//
// Created by sk337 on 1/24/25.
//

#include "hwid.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

std::string GetMachineUUID() {
    HRESULT hres;

    // Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        return "COM initialization failed.";
    }

    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );

    if (FAILED(hres)) {
        CoUninitialize();
        return "COM security initialization failed.";
    }

    // Obtain the WMI locator
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLoc
    );

    if (FAILED(hres)) {
        CoUninitialize();
        return "Failed to create IWbemLocator object.";
    }

    // Connect to WMI
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // WMI namespace
        NULL,                    // User name
        NULL,                    // User password
        0,                       // Locale
        NULL,                    // Security flags
        0,                       // Authority
        0,                       // Context object
        &pSvc                    // IWbemServices proxy
    );

    if (FAILED(hres)) {
        pLoc->Release();
        CoUninitialize();
        return "Failed to connect to WMI namespace.";
    }

    // Set security levels on the proxy
    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );

    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "Failed to set proxy blanket.";
    }

    // Query WMI for the UUID
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT UUID FROM Win32_ComputerSystemProduct"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator
    );

    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return "WMI query failed.";
    }

    // Get the data from the query
    IWbemClassObject* pClassObj = NULL;
    ULONG uReturn = 0;
    std::string uuid;

    if (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pClassObj, &uReturn);

        if (uReturn == 0) {
            uuid = "No UUID found.";
        } else {
            VARIANT vtProp;
            hres = pClassObj->Get(L"UUID", 0, &vtProp, 0, 0);
            if (SUCCEEDED(hres)) {
                uuid = _bstr_t(vtProp.bstrVal);
                VariantClear(&vtProp);
            } else {
                uuid = "Failed to retrieve UUID.";
            }
            pClassObj->Release();
        }

        pEnumerator->Release();
    }

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return uuid;
}

#else // Linux Implementation

#include <fstream>

std::string GetMachineUUID() {
    std::ifstream uuidFile("/etc/machine-id");
    if (!uuidFile.is_open()) {
        return "Failed to open UUID file.";
    }

    std::string uuid;
    std::getline(uuidFile, uuid);
    uuidFile.close();

    if (uuid.empty()) {
        return "UUID not found.";
    }

    return uuid;
}

#endif

int luaL_getHWID(lua_State *L) {
    lua_pushstring(L, GetMachineUUID().c_str());
    return 1;
}