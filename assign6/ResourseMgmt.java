// Shraddha Jamadade
// Student Id: 110287963
// CSci 117 Assignment 6
// Date: Nov 28, 2017 //__________________________________________________________________ //
// Problem Description
// Assignment to practice concurrent programming with Java Threads.
// This assignment shows Serially Reusable Recourse Management for concurrent processes.
// It is assumed that there are 2 types of Serially Reusable Resources-
// 1. SR1 with 3 units
// 2. SR2 with 2 units
// The system contains 6 concurrent processes.
// Each process acquires SR1 and SR2 (one unit each), performs operation and then releases
// those units.
// [We can consider an example where 6 students(processes) are doing the activity of creating a
// diagram using 3(units) red pens(SR1) and 2(units) blue pens(SR2)]
// 6 processes compete for accessing both SR1 and SR2
// Once a process accesses both SR1 and SR2 (one unit each), it completes its work after which
// it returns them for other processes who are waiting. //
// Input- No input data file. Code contains four classes to manage process concurrency.
// Output- Messages generated at runtime to trace the behaviour of the system:
// Thread for process_# created,
// Process_# acquires SR#,
// Process_# is waiting for SR#,
// Process_# is working,
// Process_# releases SR# //___________________________________________________________________ // Code
package sr_manager;
// Main driver class
public class sr_manager { static sr1 r1=new sr1(); static sr2 r2=new sr2(); static sr2 r3=new sr2(); static sr2 r4=new sr2(); static sr2 r5=new sr2(); static sr2 r6=new sr2();
// Defines resources r1 and r2
// Creates 6 threads for 6 processes and making them run concurrently
public static void main(String[] args) {
process p1=new process(1,r1,r2); process p2=new process(2,r1,r2); process p3=new process(3,r1,r3);
} }
process p4=new process(4,r1,r4); process p5=new process(5,r1,r5); process p6=new process(6,r1,r6);
// Start processes p1 to p6
p1.start(); p2.start(); p3.start(); p4.start(); p5.start(); p6.start();
// Class declaration for shared resource r1
// If any resource is unavailable, the process should wait
// The process acquires the resource when it becomes available.
// acquire( ) and release( ) are defined as synchronized methods for mutual // exclusion // wait( ) and notify( ) are used for synchronization
class sr1
{
private static int avail1 = 3;
//synchronized method cannot be interrupted
//only one thread can access at a time
//gives Id of thread which is waiting for resource and then acquires it public synchronized void acquire(int id)
{
try
{
if(avail1==0)
{
System.out.println("Process_"+id+" is waiting for SSR1"); wait();
}
else
{
System.out.println("Process_"+id+" acquires SR1"); avail1--;
} }
catch(Exception ex) {
System.out.println(ex.getMessage()); }
}
} }
//synchronized method cannot be interrupted
//only one thread can access at a time
//Gives Id of the process that has released the resource //Takes process Id as input parameter
public synchronized void release(int id)
{
try
{
System.out.println("Process_"+id+" releases SR1"); ++avail1;
if(avail1==1)
{
notify(); }
}
catch(Exception ex) {
System.out.println(ex.toString()); }
//Class for shared resource r2
//A monitor class for the serially reusable resource type2(r2)
//encapsulates data available and related operations on that data
//acquire( ) and release( ) are defined as synchronized methods for mutual //exclusion //wait( ) and notify( ) are used for synchronization
class sr2
{
private static int avail2 = 2;
//synchronized method cannot be interrupted
//only one thread can access at a time
//gives id of the thread that is waiting for the resource and acquires public synchronized void acquire(int id)
{
try
{
if(avail2==0)
//the resource
{
System.out.println("Process_"+id+" is waiting for SR2"); wait();
}
else
{
} }
System.out.println("Process_"+id+" acquires SR2");
--avail2; }
}
catch(Exception ex)
{
System.out.println(ex.getMessage());
} }
//synchronized method cannot be interrupted //only one thread can access at a time
//gives the process id that has released the resource public synchronized void release(int id)
{
try
{
System.out.println("Process_"+id+" releases SR2"); ++avail2;
if(avail2==1)
{
notify(); }
}
catch(Exception ex) {
System.out.println(ex.toString()); }
//Thread class for the working process
//Acquires both SR1 and SR2 (1 unit each)
//performs operation (simply displaying a message), and releases both SR1 //and SR2 //sleep( ) is used before each call for tracing the system
//acquire( ) or release( ) are used for synchronization
class process extends Thread //thread class name is "process"
{
private int id; static sr1 r1; static sr2 r2;
//gives id of currently working process
public process(int k,sr1 r1,sr2 r2) {
id=k; this.r1=r1;
//constructor
 
this.r2=r2;
System.out.println("===== Thread for process_"+id+" created"); }
//acquire r1 and r2
//display "process_i is working" //release r1 and r2
public void run() {
try
{
r1.acquire(id);
Thread.sleep(100); r2.acquire(id);
System.out.println("---- Process_"+id+" is working currenlty"); r1.release(id);
Thread.sleep(100); r2.release(id);
}
catch(Exception ex) {
System.out.println(ex.toString()); }
 } }