#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
          
int node;
int level;
int ccr;
int cpu;
int times;
int test;
int slbetter=0;
int lstbetter=0;
int same=0; 
void init();


class dgp{
  public:
     dgp();
     int maxsl;
     int maxlst;
     int *lvnum;
     int *sl;
     int *lst;
     int *est;
     int *sl_cpu;
     int *slsorting_arr;
     int *lstsorting_arr;
     int *slsortuse;
     int *slendtime;
     int *slselectcpu;
     int **caculatecost;
     int **transtochild;
     int **transtoparent;
     int getmaxsl(int currentnode);
     int getmaxest(int currentnode);
     int getminlst(int currentnode);
     int findmaxendtime(int currentnode,int currentcpu);
     int getest();    
     void determinlv();
     void determintranscost();
     void determincc();
     void sl_level();
     void lst_level();
     void est_level();
     void dgptest();
     void test_data();
     void sort_sl();
     void sort_lst();
         
      
};
dgp::dgp()
{
     maxsl=0;
     maxlst=0;     
     determinlv();
     determincc();  
     determintranscost(); 
     
     if(test==1)
     test_data();    //啟用測試資料時 CIN請填入 10  10  1  3  1 
     
     sl_level();
     est_level();
     lst_level();
     sort_sl(); 
     sort_lst(); 
     dgptest();
     if(maxsl>maxlst)
     lstbetter++;
     else if(maxlst>maxsl)
     slbetter++; 
     else if(maxlst==maxsl)
     same++;
}
void dgp::test_data()
{
     caculatecost=new int*[node];  //給一個初始caculatecost值 
     for(int x=0;x<node;x++)
     {
     caculatecost[x]=new int [3];
     }
     
    caculatecost[0][0]=20;
    caculatecost[1][0]=20;
    caculatecost[2][0]=20;
    caculatecost[3][0]=15;
    caculatecost[4][0]=5;
    caculatecost[5][0]=5;
    caculatecost[6][0]=10;
    caculatecost[7][0]=15;
    caculatecost[8][0]=20;
    caculatecost[9][0]=20;
     for(int x=0;x<10;x++)    //初始化陣列 
     for(int y=0;y<10;y++)
     {
     transtochild[x][y]=0;
     transtoparent[x][y]=0;
     }
     
    transtochild[0][1]=8; transtoparent[1][0]=8;
    transtochild[0][2]=4; transtoparent[2][0]=4;
    transtochild[0][3]=2; transtoparent[3][0]=2;
    transtochild[0][4]=8; transtoparent[4][0]=8;
    transtochild[0][5]=4; transtoparent[5][0]=4;
    transtochild[1][7]=4; transtoparent[7][1]=4;
    transtochild[1][8]=8; transtoparent[8][1]=8;
    transtochild[2][6]=8; transtoparent[6][2]=8;
    transtochild[3][7]=8; transtoparent[7][3]=8;
    transtochild[3][8]=2; transtoparent[8][3]=2;
    transtochild[4][8]=8; transtoparent[8][4]=8;
    transtochild[5][7]=8; transtoparent[7][5]=8;
    transtochild[6][9]=2; transtoparent[9][6]=2;
    transtochild[7][9]=4; transtoparent[9][7]=4;
    transtochild[8][9]=8; transtoparent[9][8]=8;
     
}     
void dgp::dgptest()
{
      ///////////////////////////////////////////////////測試區//////////////    
  /*   
     for(int x=0;x<node;x++)
     {
     for(int y=0;y<node;y++)
     cout<<transtochild[x][y]<<" ";
     cout<<endl;
     } 
     cout<<"----------------------------------------"<<endl;
     for(int x=0;x<node;x++)
     {
     for(int y=0;y<node;y++)
     cout<<transtoparent[x][y]<<" ";
     cout<<endl;
     }
      cout<<"----------------------------------------"<<endl;
     for(int x=0;x<level;x++)
     cout<<lvnum[x]<<endl;
      cout<<"----------------------------------------"<<endl;
      for(int x=0;x<node;x++)
     cout<<caculatecost[x][0]<<" "<<caculatecost[x][1]<<" "<<caculatecost[x][2]<<endl;
      cout<<"----------------------------------------"<<endl;
      for(int x=0;x<node;x++)
      cout<<sl[x]<<endl; 
      cout<<"----------------------------------------"<<endl; 
      for(int x=0;x<node;x++)
      cout<<est[x]<<endl;
       cout<<"----------------------------------------"<<endl; 
      for(int x=0;x<node;x++)
      cout<<lst[x]<<endl;    
  */  
/////////////////////////////////////////////////////////////////////////// 
 cout<<"SL: "<<maxsl<<" LST: "<<maxlst<<endl;    
     
}
void dgp::lst_level()
{
     //////////////////首先要得出est中的最大值
     int max=0;
     for(int x=0;x<node;x++)
     {
     if(est[x]>max)
     max=est[x];       
     }        
          
     lst=new int[node];
     for(int x=0;x<node;x++)
     {
     lst[x]=0;        
     }   
     
      for(int x=node-lvnum[level-1];x<node;x++) //給EXIT NODE 初始值為EST中最大值 
     {
     lst[x]=max;        
     } 
     
      for(int x=node-lvnum[level-1]-1;x>-1;x--) //給EXIT NODE 初始值為EST中最大值 
     {
     lst[x]=getminlst(x)-caculatecost[x][0];        
     }  
     
      lstsorting_arr=new int[node];
     for(int x=0;x<node;x++)
     {
     lstsorting_arr[x]=0;        
     }   
     
           
     for(int x=0;x<node;x++)
     {
     lstsorting_arr[x]=lst[x];        
     }     
     
}
int dgp::getminlst(int currentnode)
{
     int thisnodemin=0;
     int min=9999;
      for(int x=0;x<node;x++)
     {
     if(transtochild[currentnode][x]!=0)
      {
      thisnodemin=lst[x]-transtoparent[x][currentnode];
      if(thisnodemin<min)
      min=thisnodemin;
      }
     }     
     return min;
}    
void dgp::est_level()
{

     est=new int[node];
     for(int x=0;x<node;x++)
     {
     est[x]=0;        
     } 
      
      
     
  
      for(int x=0;x<node;x++)      
     {
             
     est[x]= getmaxest(x);
  
     }   
     
     
}
int dgp::getmaxest(int currentnode)
{
     int thisnodeest=0;    
     int maxest=0;
    
      for(int x=0;x<node;x++)
     {
     if(transtoparent[currentnode][x]!=0) 
     thisnodeest=est[x]+caculatecost[x][0]+ transtochild[x][currentnode];
     if(thisnodeest>maxest)
     maxest=thisnodeest;   
     }     
     return maxest;

}     
int dgp::getest()
{
    
         


}
void dgp::sort_lst()
{
       int pointer=0;
          int cpu_pointer=0;
          int max=0;
          int min=99999;
          int cpu_min=99999; 
          
     slendtime=new int[node];
     for(int x=0;x<node;x++)
     {
     slendtime[x]=0;        
     }
     
     slselectcpu=new int[node];
     for(int x=0;x<node;x++)
     {
     slselectcpu[x]=0;        
     }
      
     sl_cpu=new int[cpu];
     for(int x=0;x<cpu;x++)
     {
     sl_cpu[x]=0;        
     }
      
     slsortuse=new int[cpu];
     for(int x=0;x<cpu;x++)
     {
     slsortuse[x]=0;        
     }     
     for(int x=0;x<node;x++)
     {
           pointer=0; //現在指向的NODE 
           cpu_pointer=0;
           max=0;
           cpu_min=99999; 
           min=99999;
              
             
             
             
        for(int y=0;y<node;y++)  ////////開始搜尋LST  擁有最小值的NODE等於POINTER 
        {
        if(lstsorting_arr[y]<min)
           {                     
           min=lstsorting_arr[y];
           pointer=y; 
           } 
        }
        
   //     cout<<pointer<<" "; 
        
        
        for(int y=0;y<cpu;y++)/////////////選哪個CPU可以最快執行     
        {
        
        slsortuse[y]=findmaxendtime(pointer,y);  //所有父節點+傳輸都完成的時間   會得出像論文中 0 0 0; 20 28 28 之類的陣列 
         
        }
        
 /*        for(int y=0;y<cpu;y++)/////////////測試用     
        {
         cout<<slsortuse[y]<<" ";
        }
        cout<<endl;*/ 
        
        
          for(int y=0;y<cpu;y++)/////////////找出當中的最小值     
        {
        
          if(slsortuse[y]<cpu_min)
          {
          cpu_min=slsortuse[y]; 
          cpu_pointer=y;
          }
        }
         
         slendtime[pointer]= slsortuse[cpu_pointer]+caculatecost[pointer][0];
         sl_cpu[cpu_pointer]=slsortuse[cpu_pointer]+caculatecost[pointer][0];///////////////////把資料填入 
        
         lstsorting_arr[pointer]=99999;//將填入的值移除
         slselectcpu[pointer]=cpu_pointer;
         
        
     }
 /*       for(int y=0;y<node;y++)/////////////測試用     
        {
         cout<<" :"<<slendtime[y]<<" ";
        }
        cout<<endl;*/ 
        
        
        
         for(int y=0;y<node;y++)/////////////找出最大的LSTENDTIME     
        {
         if(slendtime[y]>maxlst)
         maxlst=slendtime[y];
        }
        
     
}     
void dgp::sort_sl()
{
          int pointer=0;
          int cpu_pointer=0;
          int max=0;
          int cpu_min=9999; 
          
     slendtime=new int[node];
     for(int x=0;x<node;x++)
     {
     slendtime[x]=0;        
     }
     
     slselectcpu=new int[node];
     for(int x=0;x<node;x++)
     {
     slselectcpu[x]=0;        
     }
      
     sl_cpu=new int[cpu];
     for(int x=0;x<cpu;x++)
     {
     sl_cpu[x]=0;        
     }
      
     slsortuse=new int[cpu];
     for(int x=0;x<cpu;x++)
     {
     slsortuse[x]=0;        
     }     
     for(int x=0;x<node;x++)
     {
           pointer=0; //現在指向的NODE 
           cpu_pointer=0;
           max=0;
           cpu_min=9999; 
          
              
             
             
             
        for(int y=0;y<node;y++)  ////////開始搜尋SL最大值  擁有最大值的NODE等於POINTER 
        {
        if(slsorting_arr[y]>max)
           {                     
           max=slsorting_arr[y];
           pointer=y; 
           } 
        }
        
   //     cout<<pointer<<" "; 
        
        
        for(int y=0;y<cpu;y++)/////////////選哪個CPU可以最快執行     
        {
        
        slsortuse[y]=findmaxendtime(pointer,y);  //所有父節點+傳輸都完成的時間   會得出像論文中 0 0 0; 20 28 28 之類的陣列 
         
        }
        
  /*       for(int y=0;y<cpu;y++)/////////////測試用     
        {
         cout<<slsortuse[y]<<" ";
        }
        cout<<endl;*/ 
        
        
          for(int y=0;y<cpu;y++)/////////////找出當中的最小值     
        {
        
          if(slsortuse[y]<cpu_min)
          {
          cpu_min=slsortuse[y]; 
          cpu_pointer=y;
          }
        }
         
         slendtime[pointer]= slsortuse[cpu_pointer]+caculatecost[pointer][0];
         sl_cpu[cpu_pointer]=slsortuse[cpu_pointer]+caculatecost[pointer][0];///////////////////把資料填入 
        
         slsorting_arr[pointer]=0;//將填入的值移除
         slselectcpu[pointer]=cpu_pointer;
         
        
     }
  /*      for(int y=0;y<node;y++)/////////////測試用     
        {
         cout<<" :"<<slendtime[y]<<" ";
        }
        cout<<endl;*/ 
         
          for(int y=0;y<node;y++)/////////////找出最大的SLENDTIME     
        {
         if(slendtime[y]>maxsl)
         maxsl=slendtime[y];
        } 
     
} 
int dgp::findmaxendtime(int currentnode,int currentcpu)//這個涵式可以算出當前這個NODE最早可以開始的時間 
{
    int lasttime=0;
    int maxendtime=0;
    int currenttime=0;
     for(int x=0;x<node;x++)
             { 
                                                  
              if(transtoparent[currentnode][x]!=0) 
                {
                if(slendtime[x]>maxendtime)                                   
                   {
                    maxendtime=slendtime[x];                                                              
                                                                                                                  
                   }                                                              
                }                              
             }        
    
    
    
    
    
      for(int x=0;x<node;x++)
     {
         if(transtoparent[currentnode][x]!=0) 
         {
                                    
                                              
                                              
         if(slselectcpu[x]==currentcpu)
          {
           if(sl_cpu[currentcpu]>=maxendtime)                                 
           currenttime=sl_cpu[currentcpu];
           else
           currenttime=maxendtime;
          }
          else if(slselectcpu[x]!=currentcpu)
          {

          if(slendtime[x]+transtoparent[currentnode][x]<maxendtime && maxendtime>=sl_cpu[currentcpu])
          currenttime=maxendtime;
          else if(slendtime[x]+transtoparent[currentnode][x]>=maxendtime && slendtime[x]+transtoparent[currentnode][x]>=sl_cpu[currentcpu])
          currenttime=slendtime[x]+transtoparent[currentnode][x];
          else
          currenttime= sl_cpu[currentcpu];
          }   
              
              
        
          
          
                                         
         }
         
         if(currenttime>lasttime)
         lasttime=currenttime;
     }     
    
    return lasttime;
}             
void dgp::sl_level()
{
     sl=new int[node];
     for(int x=0;x<node;x++)
     {
     sl[x]=0;        
     }   
     for(int x=node-1;x>-1;x--)
     {
     sl[x]=caculatecost[x][0]+getmaxsl(x);        
     } 
     
     slsorting_arr=new int[node];
     for(int x=0;x<node;x++)
     {
     slsorting_arr[x]=0;        
     }   
     
           
     for(int x=0;x<node;x++)
     {
     slsorting_arr[x]=sl[x];        
     }    
}

int dgp::getmaxsl(int currentnode)
{
     int maxsl=0;
     for(int x=0;x<node;x++)
     {
     if(transtochild[currentnode][x]!=0 && sl[x]>=maxsl) 
     maxsl=sl[x];       
     } 
     return maxsl;       
}         
void dgp::determincc()
{
     caculatecost=new int*[node];  //給一個初始caculatecost值 
     for(int x=0;x<node;x++)
     {
     caculatecost[x]=new int [3];
     }
     for(int x=0;x<node;x++)
          {    
          caculatecost[x][1]=60+((rand()%50-30)*ccr);
          caculatecost[x][2]=30+((rand()%25-10)*ccr);
          caculatecost[x][0]=(caculatecost[x][1]+caculatecost[x][2])/2;
          }
     
}     
void dgp::determinlv()
{
     int avenum_lv=node/level;
     int total_move=0;
     lvnum=new int[level];
     for(int x=0;x<level;x++)//將每一個LEVEL NODE數先初始化為node/level 
         lvnum[x]=avenum_lv;   
     for(int x=0;x<level-1;x++)//將每一個level node 數作亂數調整 但總合依舊為node數 
         {
             int move=(avenum_lv/2)+total_move;
             int r=(rand()% avenum_lv)-move;   
             lvnum[x]=lvnum[x]+r;
             total_move=total_move+r;
             
         }                  
             lvnum[level-1]=lvnum[level-1]-total_move;
             
          
}          
void dgp::determintranscost()
{
     int pointer=0;        //pointer 指向當前LV第一個NODE 
   
     
     transtochild=new int*[node];
     transtoparent=new int*[node];
     for(int x=0;x<node;x++)
     {
     transtochild[x]=new int [node];
     transtoparent[x]=new int [node];
     }
     
     
     for(int x=0;x<node;x++)    //初始化陣列 
     for(int y=0;y<node;y++)
     {
     transtochild[x][y]=0;
     transtoparent[x][y]=0;
     }
   
     for(int x=0;x<level-1;x++)  //隨機給連接    //最後一個level不用做 因為是EXIT        
     {
            for(int y=pointer;y<pointer+lvnum[x];y++)
            {        
                    for(int z=pointer+lvnum[x];z<pointer+lvnum[x]+lvnum[x+1];z++)   
                    {
                    int c=rand()%10+1;        
                    int r=rand()%lvnum[x+1]+1;
                    if(r==1)
                    transtochild[y][z]=c;        
                          
                    }
                    
                    
                    int flag=0; //偵測有沒有NODE沒連到 
                    for(int w=0;w<node;w++)
                    {
                    if(transtochild[y][w]==1)
                    flag=1;        
                    }
                    if(flag==0)
                    {
                    int c=rand()%10+1;           
                    int r=rand()%lvnum[x+1]; 
                    transtochild[y][pointer+lvnum[x]+r]=c; 
                           
                    }
                    
                    
                    int flag2=0;//偵測有沒有NODE沒被連到 
                     for(int z2=pointer+lvnum[x];z2<pointer+lvnum[x]+lvnum[x+1];z2++)   
                    {
                             for(int w=0;w<node;w++)
                             {
                             if(transtochild[z2][w]==1)
                              flag2=1;        
                             }
                             if(flag2==0)
                             {
                              int c=rand()%10+1;          
                              int r=rand()%lvnum[x];
                               transtochild[pointer+r][z2]=c;
                               
                             }     
                            
                    }
                                               
            }
            pointer=pointer+lvnum[x];
     } 
     
  
      for(int x=0;x<node;x++)//設定有哪些點連到父節點陣列 
     {
    
              for(int y=0;y<node;y++)
             
              transtoparent[y][x]= transtochild[x][y];
              
                 
     } 
     
          
}               

int main()
{
    
 init();  
 dgp *test; 
 test=new dgp[times];
 
 cout<<"HLFET比較好的CASE數:"<<slbetter<<endl;
 cout<<"MCP比較好的CASE數:"<<lstbetter<<endl;
 cout<<"一樣的CASE數:"<<same<<endl;    
 system("pause");   
}    

void init()
{
 srand(time(NULL)); 
 cout<<"請輸入是否要用測試資料,若是請輸入10 10 1 3 1"<<endl;
 cin>>test;     
 cout<<"請輸入有幾個node"<<endl;
 cin>>node;
 cout<<"請輸入有幾個level"<<endl;
 cin>>level;
 cout<<"請輸入CCR"<<endl;
 cin>>ccr;
 cout<<"請輸入多少個CPU"<<endl;
 cin>>cpu;       
 cout<<"請輸入要測試多少次"<<endl;
 cin>>times;
    
}     
