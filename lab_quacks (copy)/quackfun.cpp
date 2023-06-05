/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    // stack<T> s_copy = s;
    if (s.empty()){
        return T();         
    }
    T stack_top = s.top();
    T total_sum;
    s.pop();
    total_sum = stack_top + sum(s);
    s.push(stack_top);
    return total_sum;

                // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    int remain = 0;
    int counter = 0;
    int size = q.size();
    for (int i = 1; counter < size; i++){
        counter += i;
        //the left-over case
        if(counter > size){
            counter -= i;
            remain = size - counter;
            counter += i;
            //if i is odd, dont reverse
            if(i%2 == 1){
                for(int j=1; j<=remain; j++){
                    q2.push(q.front());
                    q.pop();
                }
                break;
            }
            //if i is even, reverse
            else{
                //push the front of quene into the top of stack
                for(int j=1; j<=remain; j++){
                    s.push(q.front());
                    q.pop();
                }
                //pop out the top of the stack and push it into quene2
                for(int k=1; k<=remain; k++){
                    q2.push(s.top());
                    s.pop();
                }
                break;            
            }
        }
        //if i is odd, dont reverse
        if(i%2 == 1){
            for(int j=1; j<=i; j++){
                q2.push(q.front());
                q.pop();
            }
        }
        //if i is even, reverse
        else{
            //push the front of quene into the top of stack
            for(int j=1; j<=i; j++){
                s.push(q.front());
                q.pop();
            }
            //pop out the top of the stack and push it into quene2
            for(int k=1; k<=i; k++){
                q2.push(s.top());
                s.pop();
            }
        }
    }
    q = q2;
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T temp_s; //temp element for stack
    T temp_q; //temp element for quene
    
    //if both reach the endpoint, return true
    if(s.empty() || q.empty()) return true;

    //compare the element in stack and quene
    else{
        temp_s = s.top();
        s.pop();
        retval = retval && verifySame(s,q);
        s.push(temp_s);
        temp_q = q.front();
        if(temp_s == temp_q){
            q.pop();
            q.push(temp_q);

            return retval;
        }
        else{
            retval = false;
            return retval;
        }        
    }

    //if the elements doesnt equal, return false


}

}