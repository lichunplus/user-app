#include <stdio.h>
//#include "list.h"
#include "queue.h"

struct student
{
    int id;
    char *name;
    int score;
//    struct list_head list;
	QLIST_ENTRY(student) entry;
};

struct student zhao = {
    .id = 1,
    .name = "zhao",
    .score = 60,
};

struct student qian = {
    .id = 2,
    .name = "qian",
    .score = 70,
};

struct student sun = {
    .id = 3,
    .name = "sun",
    .score = 80,
};

struct student li = {
    .id = 4,
    .name = "li",
    .score = 90,
};

int main(void)
{
    /* 定义链表头，并初始化 */
//    LIST_HEAD(student_list);
   static QLIST_HEAD(, student) student_list =
    QLIST_HEAD_INITIALIZER(student_list);
   
    /* 插入元素 */
//    list_add_tail(&zhao.list, &student_list);
//    list_add_tail(&qian.list, &student_list);
//    list_add_tail(&sun.list, &student_list);
//    list_add_tail(&li.list, &student_list);
	QLIST_INSERT_HEAD(&student_list, &zhao, entry);
	QLIST_INSERT_HEAD(&student_list, &qian, entry);
	QLIST_INSERT_HEAD(&student_list, &sun, entry);
	QLIST_INSERT_HEAD(&student_list, &li, entry);



    /* 遍历链表一 */
//    struct list_head *pos;
//    struct student *ptr;
//    list_for_each(pos,&student_list)
//    {
//        ptr = list_entry(pos,struct student,list);
//        printf("ID:%d\tName:%s\tScore:%d\n",ptr->id, ptr->name, ptr->score);
//    }
	struct student *std;
    QLIST_FOREACH(std, &student_list, entry) {
        printf("ID:%d\tName:%s\tScore:%d\n",std->id, std->name, std->score);
    }
    printf("================================\n");
    /* 删除一个元素 */
//    list_del(&li.list);
	QLIST_REMOVE(&li, entry);

    /* 遍历链表二 */
//    struct student *pos1;
//    list_for_each_entry(pos1, &student_list, list)
//    {
//        printf("ID:%d\tName:%s\tScore:%d\n",pos1->id, pos1->name, pos1->score);
//    }
    
//    if(list_empty(&student_list)) {
//        printf("empty\n");
//    }
    QLIST_FOREACH(std, &student_list, entry) {
        printf("ID:%d\tName:%s\tScore:%d\n",std->id, std->name, std->score);
    }
    printf("================================\n");

    
    
    return 0;
}
