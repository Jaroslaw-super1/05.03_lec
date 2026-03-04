#include <iostream>
// fake

// Задача 1
// Неявный интерфейс Т: T(), T(const T &)


// Задача 2, 3
template < class T >
struct BiList
{
  T val;
  BiList< T > * next;
  BiList< T > * prev;
};

template < class T > BiList< T > * fake()
{
  constexpr size_t s = sizeof(BiList< T >);
  return static_cast< BiList< T > * >(::operator new(s)); // T::T()
}

template < class T > BiList< T > * addfake(BiList< T > * h)
{
  BiList< T > * r = static_cast< BiList< T > * >(::operator new(sizeof(BiList< T > *))); // T::T()
  r->next = h;
  r->prev = nullptr;
  return r;
}

template < class T > BiList< T > * rmfake(BiList< T > * h) noexcept
{
  BiList< T > * res = h->next;
  ::operator delete(h);
  return res;
}

template < class T > BiList< T > * add(BiList< T > * h, const T & d)
{
  BiList< T > mid = new BiList< T >{d, h, h->prev}; // T::T(cont T &)
  h->prev->next = mid;
  h->prev = mid;
  return mid;
}

template < class T > BiList< T > * insert(BiList< T > * h, const T & d)
{
  BiList< T > * next = new BiList< T >{d, h->next, h}; // T::T(cont T &)
  h->next->prev = next;
  h->next = next;
  return next;
}

template < class T > BiList< T > * cut(BiList< T > * h) noexcept
{
  BiList< T > * res = h->next;
  res->prev = h->prev;
  h->prev->next = res;
  delete h;
  return res;
}

template < class T > BiList< T > * erase(BiList< T > * h) noexcept
{
  return h->next = cut(h->next);
}

template < class T > BiList< T > * clear(BiList< T > * h, BiList< T > * e) noexcept
{
  while (h != e)
  {
    h = cut(h);
  }
  return h;
}

template < class T, class F > F traverse(F f, BiList< T > * h, BiList< T > * end)
{
  for (; h != end; h = h->next)
  {
    f(h->val); // F::operator()
  }
  return f; // F::F(const F&)
}

template < class T, class F > F rTraverse(F f, BiList< T > * tail, BiList< T > * end)
{
  for (; tail != end; tail = tail->prev)
  {
    f(tail->val); // F::operator()
  }
  return f; // F::F(const F&)
}

template < class T >
BiList< T > * convert(T * arr, size_t size)
{
  BiList< T > * h = fake< T >();
  BiList< T > * list = h;
  for (size_t i = 0; i < size; ++i)
  {
    try
    {
      list = insert(list, arr[i]); // T::T(cont T &)
    }
    catch (...)
    {
      clear(h, nullptr);
      throw;
    }
  }
  return h;
}


int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  BiList<int> * list = convert(arr, 5);

  BiList<int> * a = clear(list, nullptr);
  cut(a);
  return 0;
}



























/*
// Задача 2, 3
template < class T >
struct BiList
{
  T val;
  BiList< T > * next;
  BiList< T > * prev;
};


// создание пустого списка
template <typename T>
BiList<T> * createList()
{
  BiList<T> * selfptr = nullptr;

  try
  {
    selfptr = new BiList<T>;
  }
  catch (const std::bad_alloc &)
  {
    return nullptr;
  }

  try
  {
    selfptr->val = T();
  }
  catch (...)
  {
    delete selfptr;
    return nullptr;
  }

  selfptr->next = selfptr;
  selfptr->prev = selfptr;

  return selfptr;
}

// Добавление элемента перед h
template <typename T>
BiList< T > * addBefore(BiList< T > * h, const T & val) {
  if (!h)
  {
    return nullptr;
  }

  BiList< T > * node = nullptr;
  try
  {
    node = new BiList< T >{val, nullptr, nullptr};
  }
  catch (const std::bad_alloc &)
  {
    return nullptr;
  }
  
  BiList< T > * last = h->prev;

  node->prev = last;
  node->next = h;

  last->next = node;
  h->prev = node;

  return node;
}

// Добавление элемента после h
template <typename T>
BiList< T > * addAfter(BiList< T > * h, const T & val) {
  if (!h)
  {
    return nullptr;
  }

  BiList< T > * node = nullptr;
  try
  {
    node = new BiList< T >{val, nullptr, nullptr};
  }
  catch (const std::bad_alloc &)
  {
    return nullptr;
  }
  
  BiList< T > * start = h->next;

  node->prev = h;
  node->next = start;

  start->prev = node;
  h->next = node;

  return node;
}

// удаление узла (любого в том числе и фиктивного так что осторожно)
template <typename T>
BiList< T > * deleteNode(BiList< T > * h) noexcept
{
  // Правильно ведь если h = nullptr то он не будет проверять h->next и программа не помрёт?
  if (!h || h == h->next)
  {
    delete h;
    return nullptr;
  }

  BiList< T > * prevNode = h->prev;
  BiList< T > * nextNode = h->next;

  prevNode->next = nextNode;
  nextNode->prev = prevNode;

  delete h;
  return prevNode;
}

// удаление всех элементов списка по указателю на фиктивный узел
template <typename T>
void clearList(BiList< T > * h) noexcept
{
  while (h->next != h)
  {
    deleteNode(h->next);
  }
}

// удаление всего списка полностью по указателю на любой узел
template <typename T>
void sudoRm(BiList< T > * h) noexcept
{
  // Можно сказать clearList() что любой узел фиктивный т.к. всё равно удаляем весь список
  clearList(h);
  delete h;
}


// Задача 4
int main()
{
  // Массив интов
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t arr_lenght = 9;

  // Создаём список
  BiList< int > * head_fake_node = createList< int >();
  if (!head_fake_node)
  {
    return 1;
  }

  for (size_t i = 0; i < arr_lenght; i++)
  {
    BiList< int > * newNode = addBefore(head_fake_node, arr[i]);
    if (!newNode)
    {
      sudoRm(head_fake_node);
      return 2;
    }
  }

  sudoRm(head_fake_node);

  return 0;
}
*/