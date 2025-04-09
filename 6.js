function customSort(...input) {
    const evens = []; // четные
    const odds = []; // нечетные

    input.forEach(num => {
        if (num === 0) {
            return;
        }

        if (num % 2 === 0) {
            evens.push(num);
        } else {
            odds.push(num);
        }
    });

    evens.sort((a, b) => b - a); // по убыванию
    odds.sort((a, b) => a - b);  // по возрастанию

    let evenIndex = 0;
    let oddIndex = 0;

    const result = input.map(num => {
        if (num === 0) {
            return 0;
        }
        if (num % 2 === 0) {
            return evens[evenIndex++];
        }
        return odds[oddIndex++];
    });

    return result;
}

console.log(customSort(5, 3, 2, 0, 8, 1, 0, 4)); // [1, 3, 8, 0, 4, 5, 0, 2]
console.log(customSort(0, 7, 6, 0, 3, 2)); // [0, 3, 6, 0, 7, 2]
