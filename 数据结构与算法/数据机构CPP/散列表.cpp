#define HashMaxSize 1000
typedef int KeyType;
typedef int ValueType;
typedef size_t (*HashFunc)(KeyType key);
//哈希表的结构
typedef enum
{                                                                                                                                  
    Empty,//空状态
    Valid,//有效状态
    Delete,//被删改的状态
}Stat;
typedef struct HashElem
{
    KeyType key;
    ValueType value;
    struct HashElem* next;
}HashElem;
typedef struct HashTable
{
    HashElem* data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;
//哈希表的初始化操作
void HashInit(HashTable* hashtable,HashFunc hash_func)
 {
    if(hashtable == NULL)
    {
         //非法操作
         return ;
    }
    hashtable->size = 0;
    hashtable->func = hash_func;
    size_t i = 0;
    for(;i < HashMaxSize ; ++i)
    {
        hashtable->data[i] = NULL;
    }
    return ;
}
//哈希表的销毁操作
void HashDestroy(HashTable* hashtable)
{
    if(hashtable == NULL)
    {
        return ;
    }
    hashtable->size = 0;
    hashtable->func = NULL;
    //遍历所有链表进行释放内存
    size_t i = 0;
    for(;i < HashMaxSize ; ++i)
    {
        HashElem* cur = hashtable->data[i];
        while(cur != NULL)
        {
            HashElem* next = cur->next;
            DestroyElem(cur);
        }
        cur = cur->next;
    }
        return ;
}
void DestroyElem(HashElem* cur)
{
    free(cur);
}
//哈希表的插入操作
void HashInsert(HashTable* hashtable,KeyType key,ValueType value)
{
    if(hashtable == NULL)
    {
        return ;
    }
    //1.根据key计算出offset
    size_t offset = hashtable->func(key);
    //2.在offset对应的链表中查找看当前的key是否存在,若存在就认为插入失败
    HashElem* ret = HashBackedFind(hashtable->data[offset],key);
    if(ret = NULL)
    {
        //找到了，说明找到了重复key的值，认为插入失败
        return ;
    }
        //3.若不存在就可以插入，使用头插法
    HashElem* new_node = CreateElem(key,value);
    //头插法
    new_node->next = hashtable->data[offset];
    hashtable->data[offset] = new_node;
    //4.++size
    ++hashtable->size;
    return;
}
//查找元素key是否存在
 HashElem* HashBackedFind(HashElem* head,KeyType to_find)
{
    HashElem* cur = head;
    for(;cur != NULL ;cur = cur->next)
    {
        if(cur->key == to_find)
        {
            return cur ;
        }
    }
    return NULL;
}
//创建新节点
HashElem* CreateElem(KeyType key,ValueType value)
{
    HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}
/*
哈希表的查找操作
（1）先对哈希表及查找内容进行合法性判断
（2）根据key值来计算出offset
（3）找到对应的offset链表，遍历链表，尝试寻找元素，方法同上面的方法
 */
int HashFind(HashTable* hashtable,KeyType key,ValueType* value)
{
    if(hashtable == NULL || value == NULL)
    {
        return 0;
    }
    //1.根据key计算出offset
    size_t offset = hashtable->func(key);
    //2.找到对应的offset的链表，遍历链表，尝试找到其中的元素
    HashElem* ret = HashBackedFind(hashtable->data[offset],key);
    if(ret == NULL)
    {
        return 0;
    }
    *value = ret->value;
    return 1;
}
void HashRemove(HashTable* hashtable,KeyType key)
{
    if(hashtable == NULL)
    {
        return ;
    }
    if(hashtable->size == 0)
    {
        return ;
    }
    //1.根据key计算出offset
    size_t offset = hashtable->func(key);
    HashElem* pre = NULL;
    HashElem* cur = NULL;
    //2.通过 offset 找到对应的链表，在链表中找到指定的元素并进行删除
    int ret = HashBackedFindEx(hashtable->data[offset],key,&pre,&cur);
    if(cur == 0)
    {
        //没找到，删除失败
        return ;
    }
    if(pre == NULL)
    {
        //要删除的元素为链表的头节点
        hashtable->data[offset] = cur->next;                                                                                       
    }
    else
    {
        //不是头节点
        pre->next = cur->next;
    }
    DestroyElem(cur);
    //--size
    --hashtable->size;
    return ;
}
int HashBackedFindEx(HashElem* head,KeyType to_find,HashElem** pre_node,HashElem** cur_node)
{
    HashElem* cur = head;
    HashElem* pre = NULL;
    for(;cur != NULL;pre = cur,cur = cur->next)
    {
        if(cur->key == to_find)
        {
            break;
        }
    }
    if(cur == NULL)
    {
        return 0;
    }
    *pre_node = pre;
    *cur_node = cur;
    return 1;
}