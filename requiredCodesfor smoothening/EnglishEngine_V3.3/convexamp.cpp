#include<iostream.h>
#include<math.h>
int main()
{
 int xmod[9],gau[9];
 for (int i=0;i<4;i++)
 {
	 cout<<"enter elements of xmod";
	 cin>>xmod[i];
      
 }

for (int i=0;i<5;i++)
 {
	 cout<<"enter elements of gau1";
	 cin>>gau[i];
      
 }
for (int i = 5;i<9;i++)
		gau[i]=0;
for (int i = 4;i<9;i++)
		xmod[i]=0;
cout<<"elements of convoultion fn:"<<endl;
for (int k=0;k<(xmod.size()+win-1);k++)
{
	int dummy=0,dummy1=xmod.size();
	double sumx=0,sumy=0;

	
	
	for(int j=0;j<dummy1;j++)
	{// cout<<k-j<<endl;
       if((k-j)>0)
	   {
		sumx+=xmod[j]*gau[(k-j)];
		
	   }
	}
	cout<<sumx<<endl;
	


}


	return 0;
}