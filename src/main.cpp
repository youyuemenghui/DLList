#include "main.hpp"

int main()
{
  DLList<float> Dlist;
  Dlist.Push(5.0);
  Dlist.Push(4.0);
  Dlist.Push(3.0);
  Dlist.Push(2.0);
  Dlist.Push(1.0);
  Dlist.Append(6.0);
  Dlist.Insert(0,Dlist.Head());
  std::cout<<"链表内容:"<<std::endl;
  for(auto i:Dlist)
  {
      std::cout<<i<<std::endl;
  }
  std::cout<<"反向链表内容:"<<std::endl;
  for(auto i:Dlist.reverse_adapter())
  {
    std::cout<<i<<std::endl;
  }
  auto* value=Dlist.Pop();
  std::cout<<"delete Node :"<<*value<<std::endl;
  delete value;
  Dlist.Print();
  Dlist.ReversePrint();
	return 0;

	return 0;
}
