#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "SVdict.h"

/* A few tests of SVdict */


int main() {

    SVdict d = makeSVdict();
    // addOrUpdate(d, "c", "c");
    // assert( hasKey(d,"c") );
    // addOrUpdate(d, "b", "b");
    // assert( hasKey(d,"b") );
    // addOrUpdate(d, "a", "a");
    // assert(hasKey(d,"a"));
    addOrUpdate(d, "apple", "apple");
    assert( hasKey(d,"apple") );
    addOrUpdate(d, "orange", "orange");
    assert( hasKey(d,"orange") );
    addOrUpdate(d, "banana", "banana");
    assert(hasKey(d,"banana"));
    addOrUpdate(d, "honeydew", "melon");
    assert(hasKey(d, "honeydew"));
    addOrUpdate(d, "jackfruit", "value");
    assert(hasKey(d, "jackfruit"));
    assert( strcmp( lookup(d, "honeydew"), "melon" ) == 0 );
    
    preorderKeys(d);

    addOrUpdate(d, "pomegranate", "pom");
    assert( hasKey(d,"jackfruit") );
    assert(  !hasKey(d,"guava") );
    assert( hasKey(d, "orange") );
    assert( strcmp( lookup(d,"jackfruit"), "value") == 0);

    addOrUpdate(d, "mango", "whatever");

    //check that keys are copied, not aliased
    char aStr[10] = "pineapple";
    addOrUpdate(d, aStr, 0);
    aStr[0] = 'z';
    assert( hasKey(d,"pineapple") );

    printf("\n\nAfter adding pomegranate and mango\n\n");
    preorderKeys(d);

    disposeSVdict(d);

    printf("\ntestSVdict successful\n");
}
