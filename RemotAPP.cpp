#include <iostream>
#include <cstdlib>
using namespace std;

//calculating the number of digits in each channel
int no_of_digits(int x)
{
    int count1=0;
    int i;

    while(x>0)
    {
        x=x/10;
        count1++;
    }
    return count1;
}
//Function to calculate the number of clicks from current channel to next channel
int calculate_count(int current,int to_move,int blocked_channels[],int no_blocked)
{
    int diff;
    int count;
    int to_move_digits;
    to_move_digits=no_of_digits(to_move);
    int size=no_blocked;
    diff=abs(to_move-current);
    int i,temp=0;
    //Meaning that no clicks needed
    if (diff==0)
    return 0;
    //calculating the number of blocked channels in betweeen
    for(i=0;i<size;i++)
    {
        if(current>to_move)
        {
            if(blocked_channels[i]<current&&blocked_channels[i]>to_move)
                temp++;
        }
        else
        {
            if(blocked_channels[i]>current&&blocked_channels[i]<to_move)
                temp++;
        }
    }

    diff=diff-temp;
    if(diff<to_move_digits)
        count=diff;
    else
        count=to_move_digits;

    return count;
}
//checking whether a channel is blocked or not
int isBlocked(int blocked[],int size,int channel)
{
    for(int i=0;i<size;i++)
    {
        if(blocked[i]==channel)
        {

              return 1;
        }
    }
    return 0;

}
int main()
{
    //target_channels-channels to be seen
    //blocked channels-channels which are blocked
    int i,no_blocked,no_target_channels,m;
    int count=0,x,y,z,x1,m1,z1,n;
    int min=10000;
    int lower_index;
    int upper_index;
    //checking all the inputs for constraints
    do
     {
         cin>>lower_index;
     }while(lower_index<=0 || lower_index>10000);

    do
    {
        cin>>upper_index;
    }while(upper_index<lower_index || upper_index>10000);

    do
    {
        cin>>no_blocked;
    }while(no_blocked<0 || no_blocked>40);

    //creating an array of blocked channels
    int blocked_channels[no_blocked];

    for(i=0;i<no_blocked;i++)
    {
       do
       {
           cin>>blocked_channels[i];
       }while(blocked_channels[i]<lower_index || blocked_channels[i]>upper_index);
    }

    do
    {
        cin>>no_target_channels;
    }while(no_target_channels<1 || no_target_channels>50);

    //creating array for storing target_channels
    int target_channels[no_target_channels];

    for(i=0;i<no_target_channels;i++)
     {
         do
         {
            cin>>target_channels[i];
         }while(target_channels[i]<lower_index || target_channels[i]>upper_index || isBlocked(blocked_channels,no_blocked,target_channels[i]));
     }

    //current-current channel to_move-channel to be viewed
    int current=0,onback=0,to_move=target_channels[0];

    for(i=0;i<no_target_channels;i++)
    {
        to_move=target_channels[i];

        //First case:If it is the first channel Then we have to click the entire channel by digits
        if(i==0)
        {
            count=count+no_of_digits(target_channels[i]);
        }
        //Here no previous channel is there
        else if(i==1)
        {
             //Finding All the Possible number of clicks
             z=calculate_count(current,to_move,blocked_channels,no_blocked);
             x=calculate_count(current,upper_index,blocked_channels,no_blocked)+calculate_count(lower_index,to_move,blocked_channels,no_blocked)+1;
             m=calculate_count(upper_index,to_move,blocked_channels,no_blocked)+calculate_count(lower_index,current,blocked_channels,no_blocked)+1;

            //Then finding the minimum no_ of clicks
            min=10000;
            if(z<min)
                min=z;
            if(x<min)
                min=x;
            if(m<min)
                min=m;
                count=count+min;
        }
        //For the remaining channels
        else{
            if(to_move==current)
                count+=0;
            else if(to_move==onback)
                count++;

            else
            {
                z=calculate_count(current,to_move,blocked_channels,no_blocked);
                x=calculate_count(current,upper_index,blocked_channels,no_blocked)+calculate_count(lower_index,to_move,blocked_channels,no_blocked)+1;
                m=calculate_count(upper_index,to_move,blocked_channels,no_blocked)+calculate_count(lower_index,current,blocked_channels,no_blocked)+1;

                z1=calculate_count(onback,to_move,blocked_channels,no_blocked)+1;
                x1=calculate_count(onback,upper_index,blocked_channels,no_blocked)+calculate_count(lower_index,to_move,blocked_channels,no_blocked)+2;
                m1=calculate_count(upper_index,to_move,blocked_channels,no_blocked)+calculate_count(lower_index,onback,blocked_channels,no_blocked)+2;

            min=10000;
            if(x<min)
                min=x;
            if(m<min)
                min=m;
            if(n<min)
                min=n;
            if(z<min)
                min=z;
            if(x1<min)
                min=x1;
            if(z1<min)
                min=z1;
            if(m1<min)
                min=m1;

            count=count+min;
        }
        }
        //Assigning channel for the next iteration
        onback=current;
        current=to_move;

        }
    //Printing the Final count
    cout<<count;
    return 0;
}
