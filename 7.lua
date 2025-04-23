-- 1)
function createFib(a, b)
    return function()
        local next = a + b
        a, b = b, next
        return next
    end
end

fibA = createFib(1, 1)
print(fibA())
print(fibA(), '\n')

fibB = createFib(0, 2)
print(fibB())
print(fibB())
print(fibB(), '\n')


-- 2)
function createRandom()
    local numbers = {}
    for i = 0, 10 do
        table.insert(numbers, i)
    end

    return function()
        if #numbers == 0 then
            return false
        end
        local index = math.random(1, #numbers)
        local value = numbers[index]
        table.remove(numbers, index)
        return value
    end
end

math.randomseed(os.time()) -- генератор случайных чисел
rnd = createRandom()
for i = 1, 12 do
    print(rnd())
end
