#include <iostream>
#include <iterator>
#include <stack>

template <typename T>
void bubble_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = 0; j < length - 1 - i; j++) {
            if (array[j] > array[j + 1])
                std::swap(array[j], array[j + 1]);
        }
    }
    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void select_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    for (size_t i = 0; i < length - 1; i++) {
        int min = i;
        for (size_t j = i + 1; j < length; j++) {
            if (array[min] > array[j])
                min = j;
        }
        std::swap(array[min], array[i]);
    }
    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void insert_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    for (size_t i = 1; i < length; i++) {
        for (size_t j = 0; j < i; j++) {
            if (array[i] < array[j])
                std::swap(array[i], array[j]);
        }
    }
    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void shell_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // i is group num
    for (size_t i = length; i != 0; i /= 2) {
        // j is group count
        for (size_t j = 0; j < i; j++) {
            // insert sort every group
            for (size_t k = j + i; k < length; k += i) {
                for (size_t m = j; m < k; m += i) {
                    if (array[k] < array[m])
                        std::swap(array[k], array[m]);
                }
            }
        }
    }
    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void merge_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // i is group num
    T *src = array;
    T *buff = new T[length];
    for (size_t i = 1; i < length; i += i) {
        // j is group count
        for (size_t j = 0; j < length; j += i + i) {
            // insert sort every group
            int s1 = j, e1 = std::min(j + i, (size_t)length), s2 = e1, e2 = std::min(j + i + i, (size_t)length);
            int k = j;
            while (s1 < e1 && s2 < e2)
                buff[k++] = src[s1] < src[s2] ? src[s1++] : src[s2++];
            while (s1 < e1)
                buff[k++] = src[s1++];
            while (s2 < e2)
                buff[k++] = src[s2++];
        }
        std::swap(src, buff);
    }
    if (src != array) {
        std::copy(src, src + length, array);
        buff = src;
    }
    delete[] buff;
    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void quick_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::stack<std::pair<int, int>> range;
    range.push(std::make_pair(0, length - 1));

    while (!range.empty()) {
        std::pair<int, int> pair = range.top();
        int s = pair.first, e = pair.second - 1;
        T mid = pair.second;
        range.pop();
        if (pair.first >= pair.second)
            continue;

        while (s < e) {
            std::cout << "pre:" << s << std::endl;
            while (array[s] < array[mid] && s < e)
                ++s;
            while (array[e] >= array[mid] && s < e)
                --e;
            std::cout << "swap:" << s << "<->" << e << std::endl;
            std::swap(array[s], array[e]);
        }
        if (array[s] < array[mid])
            ++s;
        std::swap(array[s], array[mid]);

        range.push(std::make_pair(pair.first, s - 1));
        range.push(std::make_pair(s + 1, pair.second));
    }

    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void heap_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    int first_p = length / 2 - 1;

    for (int i = first_p; i >= 0; i++) {
        int left = 2 * i + 1, right = 2 * i + 2;
        if (left < length && array[left] > array[i]) {
            std::swap(array[left], array[i]);
        }
        if (right < length && array[right] > array[i]) {
            std::swap(array[right], array[i]);
        }
    }

    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <typename T>
void count_sort(T array[], int length) {
    std::cout << __FUNCTION__ << " before:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    const int max_int = 100;
    int count_array[max_int] = {0};
    for (size_t i = 0; i < length; i++) {
        ++count_array[array[i]];
    }
    for (size_t i = 1; i < max_int; i++) {
        count_array[i] += count_array[i - 1];
    }
    int sorted_array[length];
    for (size_t i = length; i > 0; i--) {
        sorted_array[--count_array[array[i - 1]]] = array[i - 1];
    }
    std::copy(sorted_array, sorted_array + length, array);

    std::cout << __FUNCTION__ << " after:";
    std::copy(array, array + length, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    int bubble_array[] = {22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70};
    // bubble_sort<int>(bubble_array, sizeof(bubble_array) / sizeof(int));
    // merge_sort<int>(bubble_array, sizeof(bubble_array) / sizeof(int));
    count_sort<int>(bubble_array, sizeof(bubble_array) / sizeof(int));
}