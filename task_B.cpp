/*
-- ПРИНЦИП РАБОТЫ --
Для полученного числа(ключа) при помощи функции hash высчитываем индекс корзины и вставляем элемент по полученному индексу.
Возможную коллизию решаем методом цепочек.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Из-за объемного параметра M вероятность коллизий минимальна.
При удалении элемента при помощи функции iter_swap найденный элемент делаем первым списке и удалем в среднем за O(1).


-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Так как мы используем хеш-функцию для вычисления корзины, то сам доступ к корзине составит O(1).
Но в данной реализации хеш-таблицы для решения возможных коллизий используется метод цепочек.
Для команды "put" временная сложность будет равна O(l), в случае если данная корзина пустая.
Для команды "get" временная сложность будет равна O(1), в случае если в данной корзине нет элементов.
Для команды "delete" временная сложность составит O(1), если в корзине хранится не более одного элемента.
Если при выполнении любой из команд выясняется, что в i-той корзине хранится N_i-тых элементов временная сложность в среднем 
будет равна O(l) + N_i. И так как вероятность попадания элемента в каждую ячейку равна 1/M, где М - число корзин в таблице,
следовательно средняя сложность операций в нашей хеш-таблице равняется O(l + N_i)*1/M ~ O(1+α), где α - коэффициент заполнения.


-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Пространственная сложность по условию задачи не превышает O(10^5).
*/

//https://contest.yandex.ru/contest/24414/run-report/80108019/

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

class HashTable{
public:
    explicit HashTable(){
    }

    ~HashTable(){}

private:
    uint32_t M{100003};//количество ключей <=100000
    uint32_t index{0};
    std::vector<std::list<std::pair<uint32_t, int32_t>>> vec{M};
    std::list<std::pair<uint32_t, int32_t>> lst;
    std::pair<uint32_t, int32_t> couple;

public:

    uint32_t hash(uint32_t &tmp_key){
        return tmp_key % M;
    }

    int32_t get(uint32_t &_key){
        index = hash(_key);
        lst = vec[index];
        for(auto it = lst.begin(); it != lst.end(); ++it)
            if(it->first==_key){
                return it->second;
            }

        return -1;
    }

    void put(uint32_t &_key, int32_t &_meaning){
        index = hash(_key);
        couple = {_key, _meaning};
        lst = vec[index];
        bool priznak = false;
        for(auto it = lst.begin(); it != lst.end(); ++it)
            if(it->first==_key){
                priznak = true;
                it->second = _meaning;
                vec[index] = lst;
                break;
            }

        if(!priznak) vec[index].push_front(couple);
    }

    int32_t del(uint32_t &_key){
        index = hash(_key);
        lst = vec[index];
        bool priznak = false;
        for(auto it = lst.begin(); it != lst.end(); ++it)
            if(it->first==_key){
                priznak = true;
                std::iter_swap(lst.begin(), it);
                int32_t value = lst.begin()->second;
                lst.pop_front();
                vec[index] = lst;
                return value;
            }

        return -1;
    }
};

int main()
{
    uint32_t n;
    std::cin >> n;
    HashTable ht;
    std::string request;

    for(uint32_t i=0;i<n;i++){
        uint32_t key;
        int32_t meaning;
        std::cin >> request;
        if(request=="get"){
            std::cin >> key;
            int32_t value = ht.get(key);
            if(value>=0) std::cout << value << std::endl;
            else std::cout << "None" << std::endl;
        }
        else if(request=="put"){
            std::cin >> key >> meaning;
            ht.put(key, meaning);
        }
        else if(request=="delete"){
            std::cin >> key;
            int32_t value = ht.del(key);
            if(value>=0) std::cout << value << std::endl;
            else std::cout << "None" << std::endl;
        }
    }

    return 0;
}
