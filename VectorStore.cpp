#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
void ArrayList<T>::ensureCapacity(int cap)
{
    if (cap > capacity)
    {
        while (cap > capacity)
        {
            capacity = ceil(capacity * 1.5);
        }

        T* tmp = new T[count];
        for (int i = 0; i < count; i++)
        {
            tmp[i] = data[i];
        }

        delete[] data;
        data = new T[capacity];
        for (int i = 0; i < count; i++)
        {
            data[i] = tmp[i];
        }
        delete[] tmp;
    }

}

template <class T>
ArrayList<T>::ArrayList(int initCapacity ) {
    data = new T[initCapacity];
    count = 0;
    capacity = initCapacity;
}


template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {    
    data = new T[other.capacity];
    for (int i = 0; i < other.count; i++)
    {
        data[i] = other.data[i];
    }
    count = other.count;
    capacity = other.capacity;
}


template <class T>
ArrayList<T>::~ArrayList() {
    // TODO
    delete[] data;
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
{
    if (this == &other) return *this;
    capacity = other.capacity;
    count = other.count;
    
    delete[] data;
    data = new T[capacity];
    for (int i = 0; i < count; i++)
    {
        data[i]  = other.data[i];
    }
    
    return *this;
}

template <class T>      
void ArrayList<T>::add(T e)
{
    if (capacity == count)
    {
        ensureCapacity(capacity + 1);
   }
    data[ count] = e;
    count++;
}

template<class T>
void ArrayList<T>::add(int index, T e)
{
    if ((index >= count) || (index < 0))
    {
        throw std::out_of_range("Index is invalid!");
    }
    if (capacity == count) // cap = count
    {
        ensureCapacity(capacity + 1);
    }
    for (int i = count ; i != index;--i)
    {
        data[i ] = data[i-1];
        

    }
    data[index] = e;
    count++;
}

template <class T>
T ArrayList<T>::removeAt(int index)
{
    T tmp;
    if ((index >= count) || (index < 0))
    {
        throw std::out_of_range("Index is invalid!");
    }
    tmp = data[index];

    for (int i = index; i < count - 1; ++i) {
        data[i] = data[i + 1];
    }
    count--;
    return tmp;
}

//template<class T>
//bool ArrayList<T>::removeItem(T item) {
//    /* Remove the first apperance of item in array and return true, otherwise return false */
//    for (int i = 0; i < count; i++)
//    {
//        if (data[i] == item) {
//            for (int j = i; j < count - 1; ++j) {
//                data[j] = data[j + 1];
//               
//            }
//            count--;
//            return true;
//        }
//    }
//    return false;
//}

template <class T>
bool ArrayList<T>::empty() const
{
    if (count == 0) return true;
    else return false;
}

template <class T>
int ArrayList<T>::size() const
{
    return count;
}

template <class T>
void ArrayList<T>::clear()
{
    delete[] data;
    count = 0;
    capacity = 10;
    data = new T[capacity];
}

template <class T>
T& ArrayList<T>::get(int index) {
    if ((index >= count) || (index < 0))
    {
        throw std::out_of_range("Index is invalid!");
    }
    return *(data + index );
}

template <class T>
T& ArrayList<T>::get(int index) const {
    if ((index >= count) || (index < 0))
    {
        throw std::out_of_range("Index is invalid!");
    }
    return *(data + index );
}
template <class T>
void ArrayList<T>::set(int index, T e)
{
    if ((index >= count) || (index < 0))
    {
        throw std::out_of_range("Index is invalid!");
    }
    data[index] = e;

}

template <class T>
int ArrayList<T>::indexOf(T item) const
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item) return i;

    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item) return true;

    }
    return false;
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T&)) const

{
std::ostringstream oss;
    oss << "[";

    for (int i = 0; i < count; i++) {
        if (item2str) {
            // dùng hàm callback do người dùng cung cấp
            oss << item2str(const_cast<T&>(data[i]));
        } else {
            // fallback: thử dùng operator<<
            oss << data[i];  
            // yêu cầu kiểu T phải có operator<<
        }

        if (i < count - 1)
            oss << ", ";
    }

    oss << "]";
    return oss.str();
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin() {
    return Iterator(this, 0);
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end() {
    return Iterator(this, count);
}

// TODO: implement other methods of ArrayList



// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    if(pList == nullptr) {
        if (index != 0)
            throw std::out_of_range("Index is invalid!");
        this->pList = nullptr;
        this->cursor = 0;
        return;
    }
    if (index < 0 || index > pList->count) {
        throw std::out_of_range("Index is invalid!");
    }

    this->pList = pList;
    this->cursor = index;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator=(const Iterator& other)
{
    if (this != &other)
    {
        this->cursor = other.cursor;
        this->pList = other.pList;
    }
    return *this;
}

template <class T>
T& ArrayList<T>::Iterator::operator*()
{
    if (pList == nullptr || cursor < 0 || cursor >= pList->count) {
        throw std::out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor];
}


template <class T>
bool ArrayList<T>::Iterator::operator!=(const Iterator& other) const
{
    if ((pList != other.pList) || (cursor != other.cursor))
    {
        return true;
    }
    return false;
}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++()
{
    if ( cursor == pList->count )  throw std::out_of_range("Iterator cannot advance past end!");   
    cursor++;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int )
{
    if (cursor == pList->count)  throw std::out_of_range("Iterator cannot advance past end!");
   
    Iterator clone;
    clone = *this;
    cursor++;
    return clone;

}

template <class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--()
{
    if (cursor == 0)  throw std::out_of_range("Iterator cannot advance past end!");
    
    cursor--;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int )
{
    if (cursor == 0)  throw std::out_of_range("Iterator cannot advance past end!");
    Iterator clone;
    clone = *this;
    --cursor;
    return clone;
}
// TODO: implement other methods of ArrayList::Iterator






// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = NULL;
    tail = NULL;
    count = 0;

    
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
clear();
}

template <class T>
void SinglyLinkedList<T>::add(T e)

{
    Node* p = new Node();
    p->data = e;
    p->next = NULL;
    if (head == NULL)
    {
        head = p;
        tail = p;

        count++;
    }
    else
    {
        Node* tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tail = p;
        tmp->next = p;
        count++;
        // co the dung tail de toi uu o day
    }

}

template <class T>
void SinglyLinkedList<T>::add(int index, T e)
{
    if ((index > count) || (index < 0))
    {
        throw std::out_of_range("Index is invalid!");
    }
     else if(index == 0) {
        Node* p = new Node();
        p->data = e;
        p->next = head;
        head = p;
       
        if (count == 0) { head = tail = p; }
        count++;
     }
     else if (index == count) {
        Node* p = new Node();
        p->data = e;
        p->next = NULL;
        tail->next = p;
        tail = p;
        count++;
    }
     else
    {
        Node* tmp = head;
        Node* p = new Node();
        p->data = e;
        p->next = NULL;
        for (int i = 0; i < index - 1; i++)
        {
            tmp = tmp->next;
        }
        p->next = tmp->next;
        tmp->next = p;
        count++;
    }
}

template <class T>
T SinglyLinkedList<T>::removeAt(int index)
{
    if ((index < 0) || (index >= count))
    {
        throw std::out_of_range("Index is invalid!");
    }
    if (index == 0)
    {
        T a;
        Node* p = head;
        
        a = p->data;
        head = head->next;
        if (count == 1) { tail = NULL;  }
        count--;
        delete p;
        return a;

    }
    T a;
    Node* tmp = head;
    Node* tmp1;
    for (int i = 0; i < index; i++)
    {
        tmp1 = tmp;
        tmp = tmp->next;
    }
    a = tmp->data;
    tmp1->next = tmp->next;
    delete tmp;
    tmp = NULL;
    
    if (index == count - 1) {  
        tail = tmp1;
    }
    count--;
    return a;
}


template <class T>
bool SinglyLinkedList<T>::removeItem(T item)
{
   if (head == nullptr) return false;
    if (head->data == item) {
        Node* del = head;
        head = head->next;
        delete del;
        count--;
        if (head == nullptr) tail = nullptr; 
        return true;
    }

    Node* prev = head;
    Node* curr = head->next;

    while (curr != nullptr) {
        if (curr->data == item) {
            prev->next = curr->next;
           if (curr->next ==NULL) tail = prev;
            delete curr;
            count--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;

}

template <class T>
bool SinglyLinkedList<T>::empty() const
{
    if (head == NULL) return true;
    else return false;
}

template <class T>
int SinglyLinkedList<T>::size() const
{
    // int a = 0;
    // Node* tmp = head;
    // while (tmp != NULL)
    // {
    //     tmp = tmp->next;
    //     a++;
    // }
    // return a;
    return count;
}

template <class T>
void SinglyLinkedList<T>::clear()
{
    Node* tmp = head;
    while (tmp != NULL)
    {
        Node* p = tmp;     
        tmp = tmp->next;  
        delete p;          
    }
    head = NULL;
    tail = NULL;
    count = 0;
}

template <class T>
T& SinglyLinkedList<T>::get(int index)
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }

    Node* tmp = head;
    for (int i = 0; i < index; i++) {
        tmp = tmp->next;
    }
    return tmp->data;
}

template <class T>
T& SinglyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }

    Node* tmp = head;
    for (int i = 0; i < index; i++) {
        tmp = tmp->next;
    }
    return tmp->data;
} //them ham 

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const
{
    int index = 0;
    Node* tmp = head;
    while (tmp != NULL)
    {
        if (tmp->data == item) return index;
        tmp = tmp->next;
        index++;
    }
    return -1;
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) const
{
    return indexOf(item) != -1;
}

template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const
{
 std::ostringstream oss;
    Node* current = head;

    while (current != nullptr)
    {
        // Mở đầu mỗi phần tử
        oss << "[";

        // Chuyển phần tử thành chuỗi
        if (item2str)
            oss << item2str(current->data);
        else
            oss << current->data;   // yêu cầu T có operator<<

        oss << "]";

        // Nếu chưa phải phần tử cuối → thêm "->"
        if (current->next != nullptr)
            oss << "->";

        current = current->next;
    }

    return oss.str();   // Trả về chuỗi kết quả
}
// TODO: implement other methods of SinglyLinkedList

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() {
return Iterator(head);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() {
    return Iterator(NULL);
}

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    current = node;
}

template <class T>

typename SinglyLinkedList<T>::Iterator&
SinglyLinkedList<T>::Iterator::operator=(const Iterator& other)
{
    if (this != &other)   
    {
        this->current = other.current;
    }
    return *this;  
}

template <class T>
T& SinglyLinkedList<T>::Iterator::operator*()
{
    if (current == NULL)
    {
          throw std::out_of_range("Iterator is out of range!") ;
    }
    return current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const
{
    if (current != other.current) return true;
    else return false;

}

template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++()
{
    if(current == NULL)  throw std::out_of_range("Iterator cannot advance past end");
    current = current->next;
    return *this;
}


template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int)
{
    if (current == nullptr)
        throw std::out_of_range("Iterator cannot advance past end!");

    Iterator tmp = *this;   
    current = current->next; 
    return tmp;           
}

// TODO: implement other methods of SinglyLinkedList::Iterator











// ----------------- VectorStore Implementation -----------------

VectorStore::VectorRecord::VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vector) {
    this->id = id;
    this->rawText = rawText;
    this->rawLength = rawText.length();
    this->vector = vector;
}

VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction) {
    this->dimension = dimension;
    this->embeddingFunction = embeddingFunction;
count =0;


}

VectorStore::~VectorStore() {
    // TODO
clear();
}

int VectorStore::size() const
{
    return count;
}

bool VectorStore::empty() const
{
    return records.empty();
}

void VectorStore::clear()
{
 for (int i = 0; i < records.size(); ++i) {
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records.clear();   // Dùng clear() của ArrayList
    count = 0;         // Đặt lại về 0

}

SinglyLinkedList<float>* VectorStore::preprocessing(string rawtext)
{
    SinglyLinkedList<float>* head = embeddingFunction(rawtext);
    while (head->size() > dimension) {
        head->removeAt(head->size()-1);
    }
    while (head->size() < dimension) {
        head->add(0.0f);
    }
    return head;
}

void VectorStore::addText(string rawtext)
{
    SinglyLinkedList<float>* vec = preprocessing(rawtext);
   

    VectorRecord* rec = new VectorRecord(count+1, rawtext, vec);
    records.add(rec);
    ++count;    

}


SinglyLinkedList<float>& VectorStore::getVector(int index)
{
    if ((index < 0) || (index >= count))
    {
        throw std::out_of_range("Index is invalid!");
    }
    return *(records.get(index)->vector);
}

string VectorStore::getRawText(int index) const
{
    if ((index < 0) || (index > count))
    {
        throw std::out_of_range("Index is invalid!");
    }
    return records.get(index)->rawText;
}

int VectorStore::getId(int index) const
{
    if ((index < 0) || (index >= count))
    {
        throw std::out_of_range("Index is invalid!");
    }
    
    return records.get(index)->id;
}

bool VectorStore::removeAt(int index)
{
    if ((index < 0) || (index >= count))
    {
        throw std::out_of_range("Index is invalid!");
    }
    delete records.get(index)->vector;
    records.removeAt(index);
    count--;
    return true;
}

bool VectorStore::updateText(int index, string newRawText)
{
    if ((index < 0) || (index >= count))
    {
        throw std::out_of_range("Index is invalid!");
    }
    delete records.get(index)->vector;
    records.get(index)->vector = preprocessing(newRawText);
    records.get(index)->rawText = newRawText;
    records.get(index)->rawLength = newRawText.size();
    return true;

}

void VectorStore::setEmbeddingFunction(SinglyLinkedList<float>* (*newEmbeddingFunction)(const
    string&))
{
    embeddingFunction = newEmbeddingFunction;
}

void VectorStore::forEach(void (*action)(SinglyLinkedList<float>&, int, string&))
{
    for ( int i =0 ; i < records.size(); i++)
    {
        VectorRecord *head  = records.get(i);
        action(*(head->vector),head->rawLength , head->rawText);
    }
}

double VectorStore::cosineSimilarity(const SinglyLinkedList<float>& v1,
    const SinglyLinkedList<float>& v2) const
{
    double dot = 0.0, normA = 0.0, normB = 0.0;
    for (int i = 0; i < v1.size(); i++) {
        float a = v1.get(i);
        float b = v2.get(i);

        dot += a * b;
        normA += a * a;
        normB += b * b;
    }

    if (normA == 0 || normB == 0) return 0.0;
    return dot / (sqrt(normA) * sqrt(normB));
}

double VectorStore::l1Distance(const SinglyLinkedList<float>& v1,
    const SinglyLinkedList<float>& v2)  const
{
    int d = v1.size();
  
    double distance = 0.0;
    for (int i = 0; i < d; i++) {
        distance += std::fabs(v1.get(i) - v2.get(i));
    }

    return distance;
}


double VectorStore::l2Distance(const SinglyLinkedList<float>& v1,
    const SinglyLinkedList<float>& v2) const
{
    int d = v1.size();
    

    double sumSquares = 0.0;
    for (int i = 0; i < d; i++) {
        double diff = v1.get(i) - v2.get(i);
        sumSquares += diff * diff;
    }

    return std::sqrt(sumSquares);
}
int VectorStore::findNearest(const SinglyLinkedList<float>& query, const string& metric) const {
    if (records.empty()) throw std::out_of_range("VectorStore is empty!");

    int bestIndex = -1;
    double bestScore;

    if (metric == "cosine") {
        bestScore = -1e9; // maximize cosine
        for (int i = 0; i < records.size(); i++) {
            double sim = cosineSimilarity(query, *(records.get(i)->vector));
            if (sim > bestScore) {
                bestScore = sim;
                bestIndex = i;
            }
        }
    } else if (metric == "euclidean") {
        bestScore = 1e18; // minimize L2
        for (int i = 0; i < records.size(); i++) {
            double dist = l2Distance(query, *(records.get(i)->vector));
            if (dist < bestScore) {
                bestScore = dist;
                bestIndex = i;
            }
        }
    } else if (metric == "manhattan") {
        bestScore = 1e18; // minimize L1
        for (int i = 0; i < records.size(); i++) {
            double dist = l1Distance(query, *(records.get(i)->vector));
            if (dist < bestScore) {
                bestScore = dist;
                bestIndex = i;
            }
        }
    } else {
        throw std::invalid_argument("metric_error");
    }

    return bestIndex;
}
int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
    if (k <= 0 || k > records.size()) throw std::invalid_argument("invalid_k_value");
    if (metric != "cosine" && metric != "euclidean" && metric != "manhattan")
        throw std::invalid_argument("metric_error");

    // Tạo mảng (index, score)
    struct Item { int idx; double score; };
    ArrayList<Item> scores;

    for (int i = 0; i < records.size(); i++) {
        double val;
        if (metric == "cosine") {
            val = cosineSimilarity(query, *(records.get(i)->vector));
        } else if (metric == "euclidean") {
            val = l2Distance(query, *(records.get(i)->vector));
        } else {
            val = l1Distance(query, *(records.get(i)->vector));
        }
        Item item = { i, val };
        scores.add(item);
    }

    // Sắp xếp (selection sort vì bạn không được dùng STL sort)
    for (int i = 0; i < scores.size() - 1; i++) {
        int best = i;
        for (int j = i + 1; j < scores.size(); j++) {
            if (metric == "cosine") {
                // maximize cosine
                if (scores.get(j).score > scores.get(best).score) best = j;
            } else {
                // minimize distance
                if (scores.get(j).score < scores.get(best).score) best = j;
            }
        }
        if (best != i) {
            Item tmp = scores.get(i);
            scores.set(i, scores.get(best));
            scores.set(best, tmp);
        }
    }

    // Lấy top-k
    int* result = new int[k];
    for (int i = 0; i < k; i++) {
        result[i] = scores.get(i).idx;
    }

    return result;
}

// TODO: implement other methods of VectorStore


// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
