
/* Simple implementation for a Stack in C

   This was implemented on a plane from EWR to LAX, in about 30 minutes

   @author Nick Gattuso
   @since 3/10/17
*/




struct stack;

typedef struct stack* Stack;

Stack makeStack(int how_many);

void pushStack(Stack s, int push);

int popStack(Stack s);

void printStack(Stack s);