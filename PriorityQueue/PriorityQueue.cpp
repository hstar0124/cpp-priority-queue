#include <iostream>
#include <vector>
using namespace std;

template<typename T, typename Predicate = less<T>>
class PriotiryQueue
{
public:

    // O(logN)
    void push(const T& data)
    {
        // 힙 구조부터 세팅
        _heap.push_back(data);

        // 힙 로직 시작
        int now = static_cast<int>(_heap.size()) - 1;

        // 루트노드까지
        while (now > 0)
        {
            // 부모 노드와 비교
            int next = (now - 1) / 2;
            //if (_heap[now] < _heap[next])
            if(_predicate(_heap[now], _heap[next]))
                break;

            // 데이터 교체
            ::swap(_heap[now], _heap[next]);
            now = next;
        }

    }

    // O(logN)
    void pop()
    {
        _heap[0] - _heap.back();
        _heap.pop_back();

        int now = 0;
        while (true)
        {
            int left = 2 * now + 1;
            int right = 2 * now + 2;

            // 리프에 도달한 경우
            if (left >= (int)_heap.size())
                break;

            int next = now;

            // 왼쪽과 비교
            if (_heap[next] < _heap[left])
                next = left;

            //if (right < _heap.size() && _heap[next] < _heap[right]))
            if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
                next = right;

            if (next == now)
                break;

            ::swap(_heap[now], _heap[next]);
            now = next;
        }
    }

    // O(1)
    T& top()
    {
        return _heap[0];
    }

    // O(1)
    bool empty()
    {
        return _heap.empty();
    }



private:
    vector<T> _heap;
    Predicate _predicate;
};

int main()
{
    // less 는 내림차순, greater는 오름차순
    PriotiryQueue<int, less<int>> pq;

    pq.push(10);
    pq.push(40);
    pq.push(30);
    pq.push(50);
    pq.push(20);
    
    int value = pq.top();
    pq.pop();
}
