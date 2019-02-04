import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
//class for student database
class Student
	{
		int roll_no;
		String dob;
		String address;
		String dept;
		String gender;
		// Contructor for saving details of a student
		Student(int t1,String t2,String t3,String t4,String t5)
		{
			roll_no=t1;
			dob=t2;
			address=t3;
			dept=t4;
			gender=t5;
		}
	}


//main class begins
public class Perfect_hashing
{
	public static void main(String []args)
	{
		Random random = new Random();//creating a random object

		//values for univeral family of Hashing
		int a = random.nextInt(101-1) + 1;
		int b = random.nextInt(101-0) + 0;
		int key=0;

		ArrayList<Student> studentList = new ArrayList<Student>();
		Student p = new Student(0,null,null,null,null);// p is variable for intializing array lists

		//reading input from file 
		try (BufferedReader br = new BufferedReader(new FileReader("hashing/inp_file.txt")))
		{

			String sCurrentLine;
			
			while ((sCurrentLine = br.readLine()) != null) 
			{
				String[] elements = sCurrentLine.split(" ");
				int k = Integer.parseInt(elements[0]);
				Student s= new Student(k,elements[1],elements[2],elements[3],elements[4]);
				studentList.add(s);
			}

		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		
		
		// finding the number stored in each slot
		List<Integer> slot = new ArrayList<Integer>(15);
		for(int x = 0; x < 15; x = x + 1) 
		{
			slot.add(0);
		}
		
		for(int i=0; i<100; i++)
		{
			if(studentList.get(i).dept.equals("Civil"))
			{
				key=((a*studentList.get(i).roll_no+b)%101)%15;
				slot.set(key,slot.get(key)+1);
			}
		}

		//defining main hash function
		List<ArrayList<Student>> main_hash = new ArrayList<ArrayList<Student>>(15);
		
		for(int i=0; i<15; i++)
		{
		main_hash.add(null);
		}
		
		for(int i=0; i<15; i++)
		{
			//definition of secondary perfect hash
			ArrayList<Student> inner_hash= new ArrayList<Student>();
			
			for(int j=0; j<(slot.get(i)*slot.get(i)); j++)
			{
				inner_hash.add(p);
			}
			main_hash.set(i,inner_hash);
		}

		//Storing Civil students to their hash table using perfect hashing
		for(int i=0; i<100; i++)
		{
			if(studentList.get(i).dept.equals("Civil"))
			{
				key=((a*studentList.get(i).roll_no+b)%101)%15;
				main_hash.get(key).set(((a*studentList.get(i).roll_no+b)%101)%(main_hash.get(key).size()),studentList.get(i));
			}
		}

		//Printing all the students corresponding to a particular department
		for(int i=0; i<main_hash.size(); i++)
		{
			for(int j=0; j<main_hash.get(i).size(); j++)
			{
				if(main_hash.get(i).get(j).roll_no!=0)
				{
				System.out.println(main_hash.get(i).get(j).roll_no);
				}
			}
		}

		String c=null;
		Scanner input = new Scanner(System.in);// Creating a scanner variable for input
		int k_search;
		// Searching of a key in O(1) time using perfect hashing
		do
		{
			System.out.println("enter the no. to be searched from above printed no.");
			k_search= input.nextInt();
			key=((a*k_search+b)%101)%15;
			if(main_hash.get(key).get(((a*k_search+b)%101)%(main_hash.get(key).size())).roll_no==k_search)
			{	
				int i=key;
				int j=((a*k_search+b)%101)%(main_hash.get(key).size());
				System.out.println("Index in main hash:" +  i + '\n' + "Index in secondary hash:" + j);
				System.out.println("dob:" + main_hash.get(i).get(j).dob);
				System.out.println("address:" + main_hash.get(i).get(j).address);
				System.out.println("dept:" + main_hash.get(i).get(j).dept);
				System.out.println("gender:" + main_hash.get(i).get(j).gender);
			}
			else
			{
				System.out.println("key not found");
			}
			System.out.println("Enter 'y' if you want to search more keys");
			c = input.next();
		}
		while(c.equals("y"));
		input.close();
	}
}
