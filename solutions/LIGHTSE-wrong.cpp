#include<stdio.h>

typedef struct point {
	long long  x;
	long long y;
	long index;
}point;

point n,e,w,s;


int main()
{
	int t;
	long i,size,index1,index2,index3,index4;
	long long x,y,eMN=0,eMS=0,wMN=0,wMS=0;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%ld", &size);
		eMN=0;eMS=0;wMN=0;wMS=0;
		n.x=-1;n.y=-1;
		s.x=1000000001;s.y=1000000001;
		e.x=-1;e.y=-1;
		w.x=1000000001;w.y=1000000001;

		for (i=1; i <= size; ++i)
		{
			scanf("%lld %lld", &x, &y);

			if (y >=n.y)
			{
				n.x = x;
				n.y = y;
				n.index = i;
			}
			/*else if(y==n.y){
				if(x<n.x){
					n.x = x;
					n.y = y;
					n.index = i;

				}

			}*/

			if (x >=e.x)
			{   
				e.x = x;
				e.y = y;
				e.index=i;
				if(e.y>=eMN){
					eMN=e.y;
					index3 = i;
				}
				if(e.y<=eMS){
					eMS=e.y;
					index4= i;
				}
			}

			if (y <= s.y)
			{
				s.x = x;
				s.y = y;
				s.index = i;
			}
			/*else if(y == s.y){
				if(x>s.x){
					s.x = x;
					s.y = y;
					s.index = i;
				}
			}*/

			if (x <= w.x)
			{   //printf("Inside West\n");
				w.x = x;
				w.y = y;
				w.index=i;
				if(w.y>=wMN){
					wMN=w.y;
					index1 = i;
				}
				if(w.y<=wMS){
					wMS=w.y;
					index2 = i;
				}
			}
		}


		if(wMN==n.y) printf("1\n%ld SE\n", index1);
		else if(wMS==s.y) printf("1\n%ld NE\n", index2);
		else if(eMN==n.y) printf("1\n%ld SW\n", index3);
		else if(eMS==s.y) printf("1\n%ld NW\n", index4);
		else if (w.y <= e.y) printf("2\n%ld NE\n%ld SW", w.index, e.index);
		else printf("2\n%ld NW\n%ld SE", w.index, e.index);

	}
	return 0;
}

