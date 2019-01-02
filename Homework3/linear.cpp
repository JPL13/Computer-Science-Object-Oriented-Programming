
bool allTrue(const double a[], int n)
{
    if(n<=0)
        return true;
    
    if(!somePredicate(a[0]))
        return false;
    
    
    return (allTrue(a+1, n-1));
    
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    int count=0;
    if(n<=0)
        return count;
    
       if( !somePredicate(a[0]))
           count++;
    return count+countFalse(a+1,n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    
    if(n<=0)
        return -1;
    if( !somePredicate(a[0]))
        return 0;
    
    int subscript=firstFalse(a+1, n-1);
    if(subscript==-1)
        return -1;
    
    return 1+firstFalse(a+1,n-1);
    
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
   
    if(n<=0)
        return -1;
    if(n==1)
        return 0;
    
    else
    {
        int temp=indexOfMin(a,n-1);
       
    if(a[temp]<=a[n-1])
        return temp;
    
    else
        return n-1;
    }
    

}

bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if(n2<=0) return true;
    if(n1<n2) return false;

    if(a1[0]!=a2[0])
    return  includes(a1+1, n1-1, a2, n2);
    
    else
     return includes(a1+1,n1-1, a2+1, n2-1);
  
}


