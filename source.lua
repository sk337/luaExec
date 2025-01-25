local mods = {}
local require = function(modName)
    return mods[modName]()
end
mods["src.lldb"] = function()
    return {name = 'lldb'}
end
mods["src.fancyTree"] = function()
    function center(str, width)
        local len = #str
        if len >= width then
            return str
        end
        local padding = math.floor((width - len) / 2)
        local left_padding = padding
        local right_padding = width - len - left_padding
        return string.rep(" ", left_padding) .. str .. string.rep(" ", right_padding)
    end

    function create_tree(height)
        local width = height * 2 - 1  -- The width of the tree at its base
        for i = 1, height do
            local stars = string.rep("*", 2 * i - 1)
            print(center(stars, width))
        end
        -- Creating the trunk
        local trunk = "*"
        print(center(trunk, width))
    end

    return {create_tree = create_tree}
end


local tree = require("src.fancyTree");
tree.create_tree(5);
print("Just a funky tree lol")

local testCount = 2

local target= "Hello, World"
local encoded = base64_encode(target)
print("test 1/"..testCount)
assert(encoded:len()%4==0, "Length of encoded in not divisible by 2")
print("test 2/"..testCount)
assert(target == base64_decode(encoded), "Decode results in different string")
print("test 3/"..testCount)
assert(1 < random_float > 0, "Random float is not in range")
print("test 4/"..testCount)
local v = random_int(0,5)
assert(0<=v<=5, "Random Int is not in range")