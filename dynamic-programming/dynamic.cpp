#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
int solution,fast,low,high,count=0; 
std::vector<std::vector <int> > table;	//table for the storing enteries in vector of vectors
std::vector<std::vector <int> > butable;  //table for storing the output values of bottoms up approach
std::vector<std::vector <int> > mod_butable; //table for storing the output values of bottoms up approach for modified question
std::vector<int> row;				//vector for storing rows
int*  memo;
char* sequence;
void bottom_up();
int top_wo_memoization(int);
int top_w_memoization(int);
void modified_bottom_up();
void printsequence();

int main()
{
	int top_wo=0,top_w=0,temp;
	std::ifstream file("dynamic-programming/input.txt");
	file.seekg(0,std::ios::beg);
	while(!file.eof() && count<7)		//reading from file
	{
	    file>>fast;
		file>>low;
		file>>high;
		row.clear();
		row.push_back(fast);
		row.push_back(low);
		row.push_back(high);
		table.push_back(row);
		count++;	
	}
	file.close();
	if(table.size()==0)
	{
		std::cout<<"no input";
		exit (0);
	}

	for(int i =0;i<table.size();i++) //printing values of table
	{
		for(int j=0;j<table[i].size();j++)
		{
			std::cout<<table[i][j]<<"\t";
		}
		std::cout<<"\n";
	}
	memo= new int[count]();
	for(int i=0;i<count;i++)
	{
		memo[i]=-10;
	}
	clock_t begin = clock();
	bottom_up();
	clock_t end = clock();
	std::cout<<"running time for bottom-up:"<<double(end - begin) / CLOCKS_PER_SEC<<"\n";


	clock_t begin1 = clock();
	top_wo=top_wo_memoization(count-1);
	std::cout<<"\n"<<"top-down without memoization:"<<top_wo<<"\n";
	clock_t end1 = clock();
	std::cout<<"running time for top-down without memoization:"<<double(end1 - begin1) / CLOCKS_PER_SEC<<"\n";
	printsequence();

	clock_t begin2 = clock();
	top_w=top_w_memoization(count-1);
	std::cout<<"\n"<<"top-down with memoization:"<<top_w<<"\n";
	clock_t end2 = clock();
	std::cout<<"running time for top-down with memoization:"<<double(end2 - begin2) / CLOCKS_PER_SEC<<"\n";
	printsequence();

	std::cout<<"modified diet plan begins\n";
	modified_bottom_up();
	return 0;
}



////////bottom-up function begins--------------------------------

	void bottom_up()
	{
		sequence = new char[count]();
	    row.clear();
	    //entring 1st row of butable table
	    row.push_back(table[0][0]);
	    row.push_back(table[0][1]);
	    row.push_back(0);
	    butable.push_back(row);
		row.clear();
		

		for(int i=1;i<table.size();i++)  //creating table for bottoms-up approach
		{
			int max=butable[i-1][0];
			for(int j=1;j<table[i].size();j++)
			{
				if(max<butable[i-1][j])
					max=butable[i-1][j];
			}
			for(int j=0;j<2;j++)
			{
				row.push_back(table[i][j]+max);
			}
			row.push_back(butable[i-1][0]+table[i][2]);
			butable.push_back(row);
			row.clear();
		}
		std::cout<<"\n";
		



		for(int i =0;i<butable.size();i++)  //printing table for the solution
		{
			for(int j=0;j<butable[i].size();j++)
			{
				std::cout<<butable[i][j]<<"\t";
			}
			std::cout<<"\n";
		}

		//getting the optimal value for the optimal solution
		solution= butable[count-1][1];
		if (solution<=butable[count-1][2])
			solution=butable[count-1][2];
		std::cout<<"\noptimal solution = "<<solution<<"\n";
		for(int i=butable.size()-1;i>=0;i--)
		{
			
			if (solution==butable[i][2])
			{
				sequence[i]='H';
				solution=solution-table[i][2];

			}
			else if(solution==butable[i][1])
			{
				sequence[i]='L';
				solution=solution-table[i][1];
			}
			else if(solution==butable[i][0])
			{
				sequence[i]='F';
				solution=solution-table[i][0];
			}
			
		}
		
		for(int i=0;i<count;i++)
		{
			std::cout<<sequence[i]<<"--";
		}
		std::cout<<"end\n";
	}
	

////////function for finding maximum--------------------------------

	int maximum(int a,int b)
	{
		if (a>b)
			return a;
		else
			return b;	
	}



////////top-down without memoization function begins--------------------------------

	int top_wo_memoization(int num)
	{
		
		int t1,t2,t3,max;
		if (num<0)
			return 0;
		else if(num==0)
			return maximum(table[num][0],table[num][1]);
		else
		{
			t1 = table[num][0]+top_wo_memoization(num-1);
			t2 = table[num][1]+top_wo_memoization(num-1);
			t3 = table[num][2]+table[num-1][0]+top_wo_memoization(num-2);
			max=t1;
			if (max<t2)
				max=t2;
			if (max<t3)
				max=t3;
			return max;
		}		
	}

////////top-down with memoization function begins--------------------------------

int top_w_memoization(int num)
	{
		int t1,t2,t3,max;
		if (memo[num]>0)
			return memo[num];
		if (num<0)
			return 0;
		else if(num==0)
		{
			memo[num]=maximum(table[num][0],table[num][1]);
			return maximum(table[num][0],table[num][1]);
		}
		else
		{
			t1 = table[num][0]+top_wo_memoization(num-1);
			t2 = table[num][1]+top_wo_memoization(num-1);
			t3 = table[num][2]+table[num-1][0]+top_wo_memoization(num-2);
			max=t1;
			if (max<t2)
				max=t2;
			if (max<t3)
				max=t3;
			memo[num]=max;
			return max;
		}	

		
	}

void printsequence()
{
	for(int i=0;i<count;i++)
	{
		std::cout<<sequence[i]<<"--";
	}
	std::cout<<"end\n";
}

///////function with modification for bonus-------------------------------------

void modified_bottom_up()
	{
		sequence = new char[count]();
	    row.clear();
	    //entring 1st row of butable table
	    row.push_back(table[0][0]);
	    row.push_back(table[0][1]);
	    row.push_back(0);
	    mod_butable.push_back(row);
		row.clear();
		

		for(int i=1;i<table.size();i++)  //creating table for bottoms-up approach
		{
			int max=mod_butable[i-1][0];
			for(int j=1;j<table[i].size();j++)
			{
				if(max<mod_butable[i-1][j])
					max=mod_butable[i-1][j];
			}
			for(int j=0;j<2;j++)
			{
				row.push_back(table[i][j]+max);
			}
			row.push_back(maximum(mod_butable[i-1][0],mod_butable[i-1][1])+table[i][2]);
			mod_butable.push_back(row);
			row.clear();
		}
		std::cout<<"\n";
		



		for(int i =0;i<mod_butable.size();i++)  //printing table for the solution
		{
			for(int j=0;j<mod_butable[i].size();j++)
			{
				std::cout<<mod_butable[i][j]<<"\t";
			}
			std::cout<<"\n";
		}

		//getting the optimal value for the optimal solution
		solution=mod_butable[count-1][1];
		if (solution<=mod_butable[count-1][2])
			solution=mod_butable[count-1][2];
		std::cout<<"\noptimal solution = "<<solution<<"\n";
		for(int i=mod_butable.size()-1;i>=0;i--)
		{
			
			if (solution==mod_butable[i][2])
			{
				sequence[i]='H';
				solution=solution-table[i][2];

			}
			else if(solution==mod_butable[i][1])
			{
				sequence[i]='L';
				solution=solution-table[i][1];
			}
			else if(solution==mod_butable[i][0])
			{
				sequence[i]='F';
				solution=solution-table[i][0];
			}
			
		}
		
		for(int i=0;i<count;i++)
		{
			std::cout<<sequence[i]<<"--";
		}
		std::cout<<"end";
	}
	
