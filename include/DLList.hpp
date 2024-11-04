#include "type.hpp"
#include <iostream>
#ifndef  __DLLIST_HPP_
#define __DLLIST_HPP_
template <typename T>
class DLLNode
{
  public:
    DLLNode():_item(T()),_prev(nullptr),_next(nullptr){};
    DLLNode(T el,DLLNode* Prevptr=nullptr,DLLNode* Nextptr=nullptr):_item(el),_prev(Prevptr),_next(Nextptr){};
    void SetData(T el){_item=el;};
    void SetNext(DLLNode* Nextptr){_next=Nextptr;};
    void SetPrev(DLLNode* Prevptr){_prev=Prevptr;};
    T GetData()const{return this->_item;};
    DLLNode* GetNext()const{return this->_next;};
    DLLNode* GetPrev()const{return this->_prev;};
  private:
    T _item;
    DLLNode *_prev;
    DLLNode *_next;
};

template <typename T>
class Iterator
{
  public:
    Iterator(DLLNode<T>* ptr):_current(ptr){}
    bool operator!=(const Iterator& other )const;
    T operator*()const;
    const Iterator& operator++();
  private:
    DLLNode<T> *_current;
};

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
  return this->_current!=other._current;
}
template <typename T>
T Iterator<T>::operator*()const
{
  return this->_current->GetData();
}
template <typename T>
const Iterator<T>& Iterator<T>::operator++()
{
  if(_current)
  {
    this->_current=this->_current->GetNext();
  }
  return *this;
}
template <typename T>
class ReverseIterator
{
  public:
    ReverseIterator(DLLNode<T>* ptr):_current(ptr){}
    bool operator!=(const ReverseIterator& other )const;
    T operator*()const;
    const ReverseIterator& operator++();
  private:
    DLLNode<T> *_current;
};

template <typename T>
bool ReverseIterator<T>::operator!=(const ReverseIterator& other)const
{
  return this->_current!=other._current;
}
template <typename T>
T ReverseIterator<T>::operator*()const
{
  return this->_current->GetData();
}
template <typename T>
const ReverseIterator<T>& ReverseIterator<T>::operator++()
{
  if(_current)
  {
    this->_current=this->_current->GetPrev();
  }
  return *this;
}

template <typename T>
class DLList
{
  public:
    DLList();
    ~DLList();
    bool IsEmpty(); //判空
    int GetLength(); //获取链表长度
    DLLNode<T>* Head(); //返回头指针
    DLLNode<T>* Tail(); //返回尾指针
    void Push(T data);
    void Insert(T data,DLLNode<T>* pos);
    void Insert(T data,long long index);
    void Append(T data);
    T* Shift();
    T* Remove(DLLNode<T>* pos);
    T* Remove(long long index);
    T* Pop();
    bool clear();   //清空链表
    bool Inlist(const DLLNode<T> *pos); //判断节点是否在链表中
    bool Inlist(const T target);  //判断数据所在节点是否在链表中
    DLLNode<T>* Find(T target)const;
    void Print()const;  //遍历打印 
    void ReversePrint()const;

    Iterator<T> begin()const;
    Iterator<T> end()const;
    ReverseIterator<T> rbegin()const;
    ReverseIterator<T> rend()const;
    class ReverseAdapter 
    {
    public:
      DLList<T>& list;
      ReverseAdapter(DLList<T>& lst) : list(lst) {}
      ReverseIterator<T> begin() { return list.rbegin();}
      ReverseIterator<T> end() { return list.rend();}
    };
    // 方法以便调用适配器
    ReverseAdapter reverse_adapter() 
    {
      return ReverseAdapter(*this);
    }
  private:
    int _Length;
    DLLNode<T> *_header,*_tail;
};

template <typename T>
DLList<T>::DLList()
{
  this->_header=this->_tail=nullptr;
  this->_Length=0;
}

template <typename T>
DLList<T>::~DLList()
{
  this->clear();
}

template <typename T>
bool DLList<T>::IsEmpty()
{
  return this->_Length==0;
}

template <typename T>
int DLList<T>::GetLength()
{
  return this->_Length;
}
template <typename T>
DLLNode<T>* DLList<T>::Head()
{
  return this->_header;
}
template <typename T>
DLLNode<T>* DLList<T>::Tail()
{
  return this->_tail;
}
template <typename T>
void DLList<T>::Push(T data)
{
  if(this->_Length==0)
  {
    this->_header=this->_tail=new DLLNode<T>(data);
    this->_Length++;
    return;
  }
    this->_header->SetPrev(new DLLNode<T>(data,this->_header->GetPrev(),this->_header));
    this->_header=this->_header->GetPrev();
    this->_Length++;
}
template <typename T>
void DLList<T>::Insert(T data,DLLNode<T>* pos)
{
  if(pos==nullptr)
  {
    std::cout<<"Error: Invalid Position"<<std::endl;
    return;
  }
  if(pos==this->_header)
  {
    this->Push(data);
    return;
  }
  DLLNode<T>* tmp;
  for(tmp=this->_header;tmp!=nullptr && tmp!=pos;tmp=tmp->GetNext());
  if(tmp!=nullptr)
  {
    tmp->SetPrev(new DLLNode<T>(data,tmp->GetPrev(),tmp));
    tmp->GetPrev()->GetPrev()->SetNext(tmp->GetPrev());
    this->_Length++;
  }
}
template <typename T>
void DLList<T>::Insert(T data,long long index)
{
  //判断索引是否合法,index<0
  if(index>(this->_Length-1) || index<0)
  {
    std::cout<<"Error:Invalid index,Insert faild"<<std::endl;
    return ;
  }
  //处理index==0
  if(index==0)
  {
    this->Push(data);
    return;
  }
  //index>0
  DLLNode<T> *tmp=this->_header;
  for(long long count=0;count<index;++count)
  {
    if(tmp==nullptr)
    {
      std::cout<< "Error:Reached end of list unexpectedly"<<std::endl;
      return;
    }
    tmp=tmp->GetNext();
  }
  tmp->SetPrev(new DLLNode<T>(data,tmp->GetPrev(),tmp));
  tmp->GetPrev()->GetPrev()->SetNext(tmp->GetPrev());
  this->_Length++;
  this->_Length++;
}
template <typename T>
void DLList<T>::Append(T data)
{
  if(this->_Length==0)
  {
    this->_header=this->_tail=new DLLNode<T>(data);
    this->_Length++;
    return;
  }
  this->_tail->SetNext(new DLLNode<T>(data,this->_tail,this->_tail->GetNext()));
  this->_tail=this->_tail->GetNext();
  this->_Length++;
}
template <typename T>
T* DLList<T>::Shift()
{
  if(this->_Length<=0)
  {
    std::cout<<"Error : list is Empty!!";
    return nullptr;
  }
  T* value_ptr{new T(this->_header->GetData())};
  if(this->_header==this->_tail)
  {
    delete this->_header;
    this->_header=this->_tail=nullptr;
    this->_Length--;
    return value_ptr;
  }
  DLLNode<T>* tmp{this->_header};
  this->_header=this->_header->GetNext();
  this->_header->SetPrev(tmp->GetPrev());
  delete tmp;
  this->_Length--;
  return value_ptr;
}
template <typename T>
T* DLList<T>::Remove(DLLNode<T>* pos)
{
  if (pos == nullptr) {
      std::cout << "Error: Invalid pos" << std::endl;
      return nullptr;
  }
  
  if (this->_Length <= 0) {
      std::cout << "Error: list is Empty!!" << std::endl;
      return nullptr;
  }

  T* value_ptr = new T(pos->GetData());
  
  // 处理单节点情况
  if (this->_Length == 1) {
      if (pos == this->_header) {
          delete pos;
          this->_header = this->_tail = nullptr;
          this->_Length--;
          return value_ptr;
      }
      delete value_ptr; // 清理已分配的内存
      return nullptr;
  }
  // 查找要删除的节点的前一个节点
  DLLNode<T>* tmp = this->_header;
  if (pos == this->_header)
  { // 处理头节点
    this->_header = pos->GetNext();
    this->_header->SetPrev(pos->GetPrev());
  } 
  else 
  {
    for(;tmp != nullptr && tmp!= pos;tmp = tmp->GetNext());
    if (tmp == nullptr)
    { // 如果没有找到 pos
          delete value_ptr;
          return nullptr;
    }
    pos->GetPrev()->SetNext(pos->GetNext());
    pos->GetNext()->SetPrev(pos->GetPrev());
    // 如果是尾节点，更新尾指针
    if (pos == this->_tail) {
        this->_tail = pos->GetPrev();
    }
  }
  delete pos; // 删除节点
  this->_Length--; // 减少长度
  return value_ptr;
}
template <typename T>
T* DLList<T>::Remove(long long index)
{
  if (this->_Length <= 0)
  {
      std::cout << "错误：列表为空！" << std::endl;
      return nullptr;
  }

  if (index < 0 || index >= this->_Length)
  {
      std::cout << "错误：索引超出范围！" << std::endl;
      return nullptr;
  }

  DLLNode<T>* current = this->_header;

  // 遍历到指定索引
  for (long long i = 0; i < index; ++i)
  {
      current = current->GetNext();
  }

  T* value_ptr = new T(current->GetData()); // 存储要删除节点的数据

  if (current->GetPrev() == nullptr) // 如果删除的是头节点
  {
      this->_header = current->GetNext();
      this->_header->SetPrev(current->GetPrev());
  }
  else // 删除非头节点
  {
      current->GetPrev()->SetNext(current->GetNext());
      current->GetNext()->SetPrev(current->GetPrev());
  }

  if (current == this->_tail) // 如果删除的是尾节点
  {
      this->_tail = current->GetPrev();
  }

  delete current; // 删除节点
  this->_Length--; // 减少长度
  return value_ptr; // 返回删除的值
}
template <typename T>
T* DLList<T>::Pop()
{
  if (this->_Length <= 0) {
      std::cout << "Error: list is Empty!!" << std::endl;
      return nullptr;
  }
  T* value_ptr=new T(this->_tail->GetData());
  if(this->_Length==1)
  {
    delete this->_tail;
    this->_header=this->_tail=nullptr;
    this->_Length--;
    return value_ptr;
  }
  DLLNode<T>* tmp=this->_tail;
  this->_tail=tmp->GetPrev();
  this->_tail->SetNext(tmp->GetNext());
  delete tmp;
  this->_Length--;
  return value_ptr;
}
template <typename T>
bool DLList<T>::clear()
{ 
  // 检查链表是否为空
  if (this->IsEmpty()) {
      return false; // 如果链表已经为空，返回false
  }

  DLLNode<T>* current = this->_header; // 从头节点开始
  DLLNode<T>* nextNode = nullptr;

  // 遍历链表并删除每个节点
  while (current != nullptr)
  {
    // 输出当前节点的数据
    std::cout << "Deleting node with data: " << current->GetData() << std::endl;
    nextNode = current->GetNext(); // 保存下一个节点
    if (nextNode != nullptr) {
        nextNode->SetPrev(current->GetPrev());
    }
    delete current; // 删除当前节点
    current = nextNode; // 移动到下一个节点
  }

  // 清空链表的头尾指针和长度
  _header = nullptr;
  _tail = nullptr;
  _Length = 0; // 更新链表长度
  return true; // 返回true表示清空成功
}
template <typename T>
bool DLList<T>::Inlist(const DLLNode<T> *pos)
{
  if(pos==nullptr)
  {
    return false;
  }
  for(DLLNode<T>* tmp=this->_header;tmp!=nullptr;tmp=tmp->GetNext())
  {
    if(tmp==pos)
    {
      return true;
    }
  }
  return false;
}
template <typename T>
bool DLList<T>::Inlist(const T target)
{
  for(auto i:*this)
  {
    if(i==target)
    {
      return true;
    }
  }
  return false;
}
template <typename T>
DLLNode<T>* DLList<T>::Find(T target)const
{
  if(this->_Length==0)
  {
    std::cout<<"Error: List is Empty!!"<<std::endl;
    return nullptr;
  }
  DLLNode<T>* tmp=this->_header;
  for(;tmp!=nullptr && tmp->GetData()!= target;tmp=tmp->GetNext());
  if(tmp==nullptr)
  {
    std::cout<<"Error: target not in list!"<<std::endl;
    return nullptr;
  }
  return tmp;
}
template <typename T>
void DLList<T>::Print()const
{
  for(auto i:*this)
  {
    std::cout << i << " "; // 打印当前节点的数据
  }
  std::cout << std::endl; // 打印换行
}
template <typename T>
void DLList<T>::ReversePrint()const
{ 
  for (auto i = rbegin(); i != rend(); ++i) 
  {
    std::cout << *i << " "; // 打印当前节点的数据
  }
  std::cout << std::endl; // 打印换行
}

template <typename T>
Iterator<T> DLList<T>::begin()const
{
  return Iterator<T>(this->_header);
}
template <typename T>
Iterator<T> DLList<T>::end()const
{
   return Iterator<T>(nullptr);
}
//反向遍历支持
template <typename T>
ReverseIterator<T> DLList<T>::rbegin()const
{
  return ReverseIterator<T>(this->_tail);
}
template <typename T>
ReverseIterator<T> DLList<T>::rend()const
{
   return ReverseIterator<T>(nullptr);
}
#endif //__DLLIST_HPP_ end
