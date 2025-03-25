/*
 * @Author: aihhhhhh aihjyhyb@outlook.com
 * @Date: 2023-11-14 11:31:55
 * @LastEditors: aihhhhhh521 aihjyhyb@outlook.com
 * @LastEditTime: 2023-11-21 14:33:51
 * @FilePath: \undefinedc:\Users\DELL\Documents\university\C_review\sort.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


//十大经典排序算法总结
//十个排序的顺序依次为：冒泡/选择/插入/希尔/归并/快速/堆/计数/桶/基数

//该总结中序列都是从1开始走到n
//待排序列的最大长度可改define N

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define N 101

typedef struct node{
    int key;
    struct node* next;
} bucket;//这里的结构是为桶排序准备的

typedef struct node1{
    int data;
    struct node1* forward;
} LSD;//这里的结构是为LSD排序准备的

int array[N];
int min(int a,int b);
int max(int a,int b);
void swap(int array[],int a,int b);
void bubble_sort(int array[],int length);
void select_sort(int array[],int length);
void insertion_sort(int array[],int length);
void shell_sort(int array[],int length);
void merge_sort_recursion(int array[],int head,int tail); void merge_sort_iteration(int array[],int length);
void quick_sort(int array[],int head,int tail);
void heap_sort(int array[],int length); void build_heap(int array[],int length); void percolate_up(int array[],int length,int target); void percolate_down(int array[],int length,int target);
void counting_sort(int array[],int length);//这里所写的计数排序最大不超过100（待排序列中元素的大小而不是数量
void bucket_sort(int array[],int length);//这里的桶设置了十个，最坏情况下最多处理100个元素，最好情况下1000个
void LSD_sort(int array[],int length);//这里只设置到两位数。

int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&array[i]);
    }
    build_heap(array,n);
    for(int i=1;i<=n;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
    heap_sort(array,n);
    for(int i=1;i<=n;i++){
        printf("%d ",array[i]);
    }
}

void insertion_sort(int array[],int length){
    for(int i=1;i<=length;i++){
        int target=array[i];
        if(i==1) continue;
        else{
            int temp=i-1;
            while(temp){
                if(array[temp]>target) swap(array,temp,temp+1);
                else break;
                temp--;
            }
        }
    }
    return;
}
//插入排序，从前到后遍历，到每一个应该比较的值时与前边排好的序列比较并插入，到序列末尾就能排列好

void bubble_sort(int array[],int length){
    for(int i=1;i<=length;i++){
        for(int j=1;j<=length-i;j++){
            if(array[j]>array[j+1]){
                swap(array,j,j+1);
            }
        }
    }
    return;
}
//冒泡排序，从前到后遍历n次，每次都将最大的数排到最末尾，就像气泡浮出水面一样

void shell_sort(int array[],int length){
    for(int step=length/2;step>=1;step/=step){
        for(int i=0;i<step;i++){
            int temp[N];
            int j=0;
            for(int i=1;i<=length;i+=step){
                j++;
                temp[j]=array[i];
            }
            insertion_sort(temp,j);
            for(int i=1,k=0;i<=length;i+=step){
                k++;
                array[i]=temp[k];
            }
        }
    }
}
//希尔排序，通过设置不同的间隔gap，将序列分为若干组，每组内都进行插入排序，直到gap=1时，进行最后一次插入排序，排序结束

void select_sort(int array[],int length){
    for(int i=1;i<length;i++){
        int target=i;
        for(int j=i;j<=length;j++){
            if(array[j]<array[target]){
                target=j;
            }
        }
        swap(array,target,i);
    }
}
//选择排序，从头到尾遍历，每次都找最小的那个值放在最前边，和冒泡算法类似，只不过是反过来的过程

void merge_sort_recursion(int array[],int head,int tail){//递归方法
    if(head>=tail){
        return;
    }
    merge_sort_recursion(array,head,(head+tail)/2);
    merge_sort_recursion(array,(head+tail)/2+1,tail);
    int start1=head,start2=(head+tail)/2+1;
    int temp[N]={0};
    for(int i=head;i<=tail;i++){
        if(start1==(head+tail)/2+1 || start2==tail+1){
            if(start1==(head+tail)/2+1){
                while(start2!=tail+1){
                    temp[i]=array[start2];
                    i+=1;start2+=1;
                }
                break;
            }
            else{
                while(start1!=(head+tail)/2+1){
                    temp[i]=array[start1];
                    i+=1;start1+=1;
                }
                break;
            }
        }
        else{
            if(array[start1]>array[start2]){
                temp[i]=array[start2];
                start2+=1;
            }
            else{
                temp[i]=array[start1];
                start1+=1;
            }
        }
    }
    for(int i=1;i<=6;i++){
        printf("%d ",temp[i]);
    }
    for(int i=1;i<=6;i++){
        printf("%d ",array[i]);
    }
    for(int j=head;j<=tail;j++){
        array[j]=temp[j];
    }
    return;
}
void merge_sort_iteration(int array[],int length){//迭代方法(还有问题，需要改)
    //对数组num归并排序迭代实现,len为数组长度，从小到大排序，O(nlog2^n)，稳定
	/*核心思想，i表示步长，也就是左右两组各几个元素比较
		，从第一轮左右每组1个开始，每轮步长增大一倍
		，比较后从小到大存入temp，再对剩余元素进行处理
		，最后将排好序的temp返回num数组
		*/

	//分别为步长、temp下标、左边起始下标、左边终点下标、右边起始下标、右边终止下标
	int i,next,left_min,left_max,right_min,right_max;
	//新建一个temp数组，长度等于初始数组长度
	int *temp = (int*)malloc(length * sizeof(int));

	//每轮比较左右两个步长i长度的区间，每轮后i*=2
	for(i=1; i<length; i*=2){

		//从数组0号开始，下一组的起始位置等于上一组的终止位置，如果下一组左边步长都不够就不比了
		for(left_min=0; left_min < length-i; left_min = right_max){
			//右边起始位置=左边终止位置=左边起始加步长i
			right_min = left_max = left_min + i;
			//右边终止位置=右边起始位置加步长i
			right_max = right_min + i;
			next = 0;//temp的下标

			if(right_max > length){//如果右边越界
				right_max = length;//右边终止位置最大值只能为len
			}

			while(left_min < left_max && right_min < right_max){//左右都没到尽头
				if(array[left_min] < array[right_min]){//左小右大，左边存入temp
					temp[next++] = array[left_min++];
				}else{//右小左大，右边存入temp
					temp[next++] = array[right_min++];
				}
			}

			/*左边还有一组剩余元素，右边已到终止位置
				，说明左边剩余元素最大，将剩余元素移到右边最后
				，如果是右边有剩余，则不需要移了已经在最后*/
			while(left_min < left_max){
				array[--right_min] = array[--left_max];
			}

			while(next > 0){//把排好序的temp部分返回num
				 array[--right_min] = temp[--next];
			}
		}
	}

}
//归并排序，利用递归机制或迭代机制,原理是分而治之，通过分为若干个序列，先将小序列中的顺序排列好，
//然后申请一段容纳两个序列大小的空间，用两个指针指向两个序列中的头部，将较小的放入申请的空间中，排序完成后再放回原序列，以此类推

void quick_sort(int array[],int head,int tail){//这里采用median3方法
    if(head>=tail) return;
    if(tail-head>5){
        int mid=(head+tail)/2,target;
        if (array[head] > array[mid])  swap(array,head,mid);
        if (array[head] > array[tail])  swap(array,head,tail);
        if (array[mid] > array[tail])  swap(array,mid,tail);
        swap(array,mid,tail-1);
        target=array[tail-1];
        int start1=head,start2=tail-1;
        for (;;) {
            while (array[++start1] < target) {}
            while (array[--start2] > target) {}
            if (start1 < start2)
                swap(array,start1,start2);
            else
                break;
        }
        swap(array,start1,tail);
        quick_sort(array,head,start1-1);
        quick_sort(array,start1+1,tail);
    }
    else{
        for (int i = head + 1; i <= tail; i++) {//插入排序
            int tmp = array[i], j = i;
            for (; j > head && array[j - 1] > tmp; j--)
                array[j] = array[j - 1];
            array[j] = tmp;
        }
        return;
    }
    return;
}
//快速排找一个pivot基准，把它放到最后，头和尾两个指针，先从前向后找有没有比pivot大的数，如果有后边的指针开始往前走，
//直到找到一个比pivot小的数，两个指针所指内容交换，当前后两指针碰面时停止，将pivot和指针所指交换，从pivot分为左右子列，依次重复

void heap_sort(int array[],int length){
    if(length==1) return;
    swap(array,1,length);
    length-=1;
    int target=length%2? (length-1)/2:length/2;
    for(int i=1;i<=target;i++){
        percolate_down(array,length,i);
    }
    heap_sort(array,length);
    return;
}
void build_heap(int array[],int length){
    int target;
    if(length%2) target=(length-1)/2;
    else target=length/2;
    for(int j=0;j<length;j++){
        for(int i=target;i>=1;i--){
            percolate_up(array,length,i);
        }
    }
    return;
}
void percolate_up(int array[],int length,int target){
    if(2*target+1>length){
        if(array[2*target]>array[target]) swap(array,2*target,target);
    }
    else{
        if(array[2*target]>array[2*target+1]){
            if(array[2*target]>array[target]) swap(array,2*target,target);
        }
        else{
            if(array[2*target+1]>array[target]) swap(array,2*target+1,target);
        }
    }
    return;
}
void percolate_down(int array[],int length,int target){
    if(2*target>length) return;
    else if(2*target+1>length){
        if(array[2*target]>array[target]) swap(array,2*target,target);
    }
    else{
        if(array[2*target]>array[2*target+1]){
            if(array[2*target]>array[target]) swap(array,2*target,target);
        }
        else{
            if(array[2*target+1]>array[target]) swap(array,2*target+1,target);
        }
    }
    return;
}
//堆排序，按照所要求的从大到小/从小到大的顺序，先建立最大/小堆，建堆过程中上滤新插入元素，建堆完成后将头和尾交换，然后从头下滤并把最后的元素取出，重复此操作
//这里由于已经相当于建好了堆，不需要那么麻烦，直接可以将堆内元素重整为最大堆，再依次下滤

void counting_sort(int array[],int length){
    int *space=malloc(sizeof(int)*101);
    for(int i=1;i<=101;i++){
        space[i]=0;
    }
    for(int i=1;i<=length;i++){
        space[array[i]]+=1;
    }
    for(int i=1,j=1;i<=length;i++){
        if(space[j]==0){
            for(int k=j;k<=101;k++){
                if(space[k]!=0){
                    j=k;
                    break;
                }
            }
        }
        array[i]=j;space[j]--;
    }
    free(space);return;
}
//计数排序，开辟一块新的空间，先计数待排序列中每个元素出现的次数并放入新开辟的区域，再将空间中的元素依次放回到原序列里，待排元素的大小有限制

void bucket_sort(int array[],int length){
    bucket* tong[10];
    for(int i=0;i<10;i++){
        tong[i]=NULL;
    }
    for(int i=1;i<=length;i++){
        int t=array[i]/10;
        if(tong[t]==NULL){
            tong[t]=(bucket*)malloc(sizeof(bucket));
            tong[t]->key=array[i];
            tong[t]->next=NULL;
        }
        else{
            bucket* p=tong[t];bucket *q=tong[t];
            while(p->next!=NULL && p->key<array[i]){
                if(p!=tong[t]){
                    q=q->next;
                }
                p=p->next;
            }
            if(p==tong[t]){
                if(p->next==NULL){
                    if(p->key<array[i]){
                        p->next=(bucket*)malloc(sizeof(bucket));
                        p->next->key=array[i];
                        p->next->next=NULL;
                    }
                    else{
                        tong[t]=(bucket*)malloc(sizeof(bucket));
                        tong[t]->key=array[i];
                        tong[t]->next=p;
                    }
                }
                else{
                    tong[t]=(bucket*)malloc(sizeof(bucket));
                    tong[t]->key=array[i];
                    tong[t]->next=p;
                }
            }
            else{
                if(p->next==NULL){
                    p->next=(bucket*)malloc(sizeof(bucket));
                    p->next->key=array[i];
                    p->next->next=NULL;
                }
                else{
                    q->next=(bucket*)malloc(sizeof(bucket));
                    q->next->key=array[i];
                    q->next->next=p;
                }
            }
        }
    }
    bucket *target=NULL;bucket *target_tail=NULL;
    for(int i=0;i<10;i++){
        if(tong[i]==NULL){
            continue;
        }
        else if(target==NULL){
            target=tong[i];
            target_tail=tong[i];
            for(;target_tail->next!=NULL;){
                target_tail=target_tail->next;
            }
        }
        else{
            target_tail->next=tong[i];
            for(;target_tail->next!=NULL;){
                target_tail=target_tail->next;
            }
        }
    }
    int i=1;
    while(i<=length){
        array[i++]=target->key;
        target=target->next;
    }
}
//桶排序，与归并排序类似，通过建立从序列到桶的映射关系，将序列细分并分别排序，最后依次将桶中的数字返回即可

void LSD_sort(int array[],int length){
    LSD* card[10];
    for(int i=0;i<10;i++){
        card[i]=NULL;
    }
    for(int i=1;i<=length;i++){
        int t=array[i]%10;
        if(card[t]==NULL){
            card[t]=(LSD*)malloc(sizeof(LSD));
            card[t]->data=array[i];
            card[t]->forward=NULL;
        }
        else{
            LSD* p=card[t];
            while(p->forward!=NULL){
                p=p->forward;
            }
            p->forward=(LSD*)malloc(sizeof(LSD));
            p->forward->data=array[i];
            p->forward->forward=NULL;
        }
    }
    LSD *target=NULL;LSD *target_tail=NULL;
    for(int i=0;i<10;i++){
        if(card[i]==NULL){
            continue;
        }
        else if(target==NULL){
            target=card[i];
            target_tail=card[i];
            for(;target_tail->forward!=NULL;){
                target_tail=target_tail->forward;
            }
        }
        else{
            target_tail->forward=card[i];
            for(;target_tail->forward!=NULL;){
                target_tail=target_tail->forward;
            }
        }
    }
    int x=1;
    while(x<=length){
        array[x++]=target->data;
        target=target->forward;
    }
    for(int i=0;i<10;i++){
        free(card[i]);
        card[i]=NULL;
    }
    for(int i=1;i<=length;i++){
        int t=array[i]/10;
        if(card[t]==NULL){
            card[t]=(LSD*)malloc(sizeof(LSD));
            card[t]->data=array[i];
            card[t]->forward=NULL;
        }
        else{
            LSD* p=card[t];
            while(p->forward!=NULL){
                p=p->forward;
            }
            p->forward=(LSD*)malloc(sizeof(LSD));
            p->forward->data=array[i];
            p->forward->forward=NULL;
        }
    }
    target=target_tail=NULL;
    for(int i=0;i<10;i++){
        if(card[i]==NULL){
            continue;
        }
        else if(target==NULL){
            target=card[i];
            target_tail=card[i];
            for(;target_tail->forward!=NULL;){
                target_tail=target_tail->forward;
            }
        }
        else{
            target_tail->forward=card[i];
            for(;target_tail->forward!=NULL;){
                target_tail=target_tail->forward;
            }
        }
    }
    int j=1;
    while(j<=length){
        array[j++]=target->data;
        target=target->forward;
    }
    return;
}
//基数排序，设置十个“桶”，先将各待排数按照个位分类（此过程不需要对每个类别细分，否则就变桶排序了），然后从0-9依次取出，再将这些数按照十位数字分类
//重复以上步骤，再次取出后就是已经排好的升序序列

int min(int x,int y){//最小值
    return x>y ? y:x;
}
int max(int x,int y){//最大值
    return x>y ? x:y;
}
void swap(int array[],int a,int b){//交换
    int temp=array[a];
    array[a]=array[b];
    array[b]=temp;
    return;
}