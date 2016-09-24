#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#define SIZE 10000


using namespace std;

class Stack
{
public:
    uint32_t SP = -1;
    uint32_t FP = -1;
    uint32_t CP = -1;
private:
    uint32_t* stack;
    size_t size;
    size_t heapStartIndex = SIZE - 1;

public:
    Stack()
    {
        size = 0;
        stack = new uint32_t[SIZE];
    }

    void setSP( int sp )
    {
        SP = sp;
        size = SP + 1;
    }
    void setFP( int fp )
    {
        FP = fp;
    }
    void setCP( int cp )
    {
        CP = cp;
    }
    void pushfp()
    {
        setSP( SP+1 );
        stack[SP] = FP;
    }
    void popfp()
    {
        FP = stack[SP];
        setSP( SP-1 );
    }
    void newfp()
    {
        FP = SP;
    }
    void pushc( const int c )
    {
        setSP( SP+1 );
        stack[SP] = c;
    }
    void rdfp( const int index )
    {
        setSP( SP+1 );
        stack[SP] = stack[ FP + index ];
    }
    void wtfp( const int index )
    {
        stack[FP + index] = stack[ SP ];
    }
    void New()
    {
        int size = stack[SP];
        heapStartIndex -= size;
        stack[SP] = heapStartIndex;
    }
    void Delete()
    {
        int index = stack[SP];
        setSP( SP - 1 );
    }
    void rd()
    {
        int index = stack[SP];
        stack[SP] = stack[index];
    }
    void wt()
    {
        int index = stack[SP];
        setSP( SP-1 );
        stack[index] = stack[SP];
    }
    void inc()
    {
        stack[SP] = stack[SP] + 1;
    }
    void dec()
    {
        stack[SP] = stack[SP] - 1;
    }
    void neg()
    {
        stack[SP] = ~stack[SP];
    }
    void add()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];
        stack[SP] = a + b;
    }
    void sub()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];
        stack[SP] = a - b;
    }
    void mul()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];
        stack[SP] = a * b;
    }
    void div()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];
        stack[SP] = a / b;
    }
    void mod()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];
        stack[SP] = a % b;
    }
    void shr()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];
        stack[SP] = a >> b;//ПОБИТОВЫЙ СДВИГ a В СТОРОНУ МЛАДШИХ БИТ НА b
    }
    void shl()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];

        stack[SP] = a << b;//ПОБИТОВЫЙ СДВИГ a В СТОРОНУ СТАРШИХ БИТ НА b
    }
    void And()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];

        stack[SP] = a & b;//ПОБИТОВЫЙ И
    }
    void  Or()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];

        stack[SP] = a | b;//ПОБИТОВЫЙ И
    }
    void  Xor()
    {
        int b = stack[SP];
        setSP(  SP - 1 );
        int a = stack[SP];

        stack[SP] = a ^ b;//ПОБИТОВЫЙ И
    }
    void swp()
    {
        int a = stack[SP];
        int b = stack[SP-1];
        stack[SP] = b;
        stack[SP-1] = a;
    }
    void dup()
    {
        setSP(SP+1);
        stack[SP] = stack[SP-1];
    }
    void pop()
    {
        setSP(SP-1);
    }
    void eq()
    {
        int a = stack[SP];
        if(a == 0)
        {
            stack[SP] = 1;
        }
        else
        {
            stack[SP] = 0;
        }
    }
    void less1()
    {
        int a = stack[SP];
        if(a < 0)
        {
            stack[SP] = 1;
        }
        else
        {
            stack[SP] = 0;
        }
    }
    void jmp( int index )
    {
        setCP( index );
    }
    void jc( int index )
    {
        int a = stack[SP];
        setSP( SP-1 );
        if(a != 0)
        {
            setCP( index );
        }
    }
    void call( int index )
    {
        setSP( SP + 1 );
        stack[SP] = CP;
        setCP( index );
    }
    void ret()
    {
        setCP( stack[SP] );
        setSP( SP - 1 );
    }
    void out()
    {
        char x = stack[SP];
        setSP(SP-1);
        cout<<x;
    }
    void in()
    {
        int input = getchar();

        setSP( SP+1 );
        stack[SP] = (int)input;
    }

}stack;

int main()
{
    setlocale(0, "RUS");
    FILE * inputFile = fopen("D:\\fibonacci.vm", "rb");
    if( inputFile == NULL )
    {
        cout << "Cannot open file." << endl;
        return 1;
    }

    fseek(inputFile , 0 , SEEK_END);
    long lSize = ftell(inputFile);
    rewind (inputFile);


    uint32_t * buffer = (uint32_t*) malloc(sizeof(uint32_t) * lSize);
    if (buffer == NULL)
    {
        cout << "Ошибка памяти" << stderr << endl;
        return 2;
    }

    size_t result = fread(buffer, lSize, 1, inputFile);
    if ((int)result != 1)
    {
        cout << "Ошибка чтения" << stderr << endl;
        return 3;
    }

    start();
    while( stack.CP < (int)sizeof(char) * lSize )
    {
        //printf("%x", buffer[stack.CP] );
        if( (uint32_t)buffer[stack.CP] == 0x0 )
        {
            stack.CP += 4;
            nop();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x1 )
        {
            stack.CP += 4;
            pushfp();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x2 )
        {
            stack.CP += 4;
            popfp();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x3 )
        {
            stack.CP += 4;
            newfp();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x4 )
        {
            int index = stack.CP+4;
            stack.CP += 8;
            pushc( buffer[index] );
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x5 )
        {
            int index = stack.CP+4;
             stack.CP += 8;
            rdfp( buffer[index] );
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x6 )
        {
            int index = stack.CP+4;
             stack.CP += 8;
            wtfp( buffer[index] );
            continue;

        }
        if( (uint32_t)buffer[stack.CP] == 0x10 )
        {
            stack.CP += 4;
            New();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x11 )
        {
            stack.CP += 4;
            Delete();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x12 )
        {
            stack.CP += 4;
            rd();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x13 )
        {
            stack.CP += 4;
            wt();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x20 )
        {
            stack.CP += 4;
            inc();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x21 )
        {
            stack.CP += 4;
            dec();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x22 )
        {
            stack.CP += 4;
            neg();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x23 )
        {
            stack.CP += 4;
            add();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x24 )
        {
            stack.CP += 4;
            sub();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x21 )
        {
            stack.CP += 4;
            dec();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x25 )
        {
            stack.CP += 4;
            mul();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x26 )
        {
            stack.CP += 4;
            div();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x27 )
        {
            stack.CP += 4;
            mod();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x28 )
        {
            stack.CP += 4;
            shr();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x29 )
        {
            stack.CP += 4;
            shl();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x2A )
        {
            stack.CP += 4;
            And();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x2B )
        {
            stack.CP += 4;
            Or();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x2C )
        {
            stack.CP += 4;
            Xor();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x30 )
        {
            stack.CP += 4;
            swp();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x31 )
        {
            stack.CP += 4;
            dup();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x32 )
        {
            stack.CP += 4;
            pop();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x40 )
        {
            stack.CP += 4;
            eq();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x41 )
        {
            stack.CP += 4;
            less1();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x50 )
        {
            int index = stack.CP + 4;
             stack.CP += 8;
            jmp( buffer[index] );
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x51 )
        {
            int index = stack.CP + 4;
             stack.CP += 8;
            jc( buffer[ index ] );
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x58 )
        {

            int index = stack.CP+4;
            //if( index  == (0x9a + 0x5) ) cout << "Yes";
            stack.CP += 8;
            call( buffer[index] );
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x59 )
        {
            stack.CP += 4;
            ret();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x80 )
        {
            stack.CP += 4;
            out();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0x81 )
        {
            stack.CP += 4;
            in();
            continue;
        }
        if( (uint32_t)buffer[stack.CP] == 0xFF )
        {
            break;
        }
    }

    fclose ( inputFile );
    return 0;
}

