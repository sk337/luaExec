Mods = {}
local require = function(modName)
    return Mods[modName]()
end
Mods["src.lldb"] = function()
    return {name = 'lldb'}
end
Mods["src.fancyTree"] = function()
    local function center(str, width)
        local len = #str
        if len >= width then
            return str
        end
        local padding = math.floor((width - len) / 2)
        local left_padding = padding
        local right_padding = width - len - left_padding
        return string.rep(" ", left_padding) .. str .. string.rep(" ", right_padding)
    end

    local function create_tree(height)
        local width = height * 2 - 1
       for i = 1, height do
            local stars = string.rep("*", 2 * i - 1)
            print(center(stars, width))
        end
        local trunk = "*"
        print(center(trunk, width))
    end

    return {create_tree = create_tree}
end


local tree = require("src.fancyTree");
tree.create_tree(5);
print("Just a funky tree lol")

local testCount = 5

local target= "Hello, World"
local encoded = base64_encode(target)
print("Test 1/"..testCount)
assert(encoded:len()%4==0, "Length of encoded in not divisible by 4")
print("Test 2/"..testCount)
assert(target == base64_decode(encoded), "Decode results in different string")
print("Test 3/"..testCount)
local rf = random_float()
assert((1 > rf) == (rf > 0), "Random float is not in range "..rf)
print("Test 4/"..testCount)
local v = random_int(0,5)
assert((0<=v)==(v<=5), "Random Int is not in range"..v)
local envrion = getEnviron()

print("test 5/"..testCount)
if envrion ~= "WINDOWS" and envrion ~= "LINUX" and envrion ~= "MACOS" and envrion ~= "UNKNOWN" then
    error("Invalid environment: " .. envrion)
end

if is_luaExec_closure then
    print("is_luaExec_closure: True")
end


if envrion == "WINDOWS" then
    local response = messageBox("Do you want to continue?", "Confirmation", 4)
end