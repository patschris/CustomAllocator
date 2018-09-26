# Custom Allocator
An implementation of a simple memory allocator that contains the functions mymalloc/myfree with the same declaration that 
can replace the malloc/free functions. This allocator uses the segregated fit strategy, that is seperated storage per object 
size class. The mymalloc/myfree functions can handle allocactions up to 4096 bytes. For larger allocations, they use standard 
malloc/free. For allocations ≤ 4096, we round the requested number of bytes up to the closer greater (or equal) power of 2, not 
less than 32 bytes. So, there are exactly 8 classes (32, 64, 128, 256, 512, 1024, 2048, 4096). For instance, mymalloc(32)⇒32, 
mymalloc(5)⇒32, mymalloc(73)⇒128.

## mymalloc
Each one of the classes will handle a double linked list that shows the pages that uses to store data. We use an array of 8 
positions that points to the 8 lists. The pages consist of 4096 bytes and they are aligned o 4096 bytes, that is every addess
of a page must be a multiple to 4096. Every page can store only objects of the same size. We allocate pages from the Operating 
System by making a malloc (at least 1 MB) and seperating the address space into pages, starting from the first multiple of 4096
in the given range of adresses. The list of each object size class handles a bit vector per page that indicates whether a page's
segment is free or occupied. When we find a free segment in the page, we allocate the segment and we move the page in the head
of the list, in order to accelarate future searches. If we can't find a free segment, we ask for a new page. Finally, every node 
that corresponds to a page is stored to a hash table in order to find quickly if a page is used from mymalloc.

![schema](https://github.com/patschris/CustomAllocator/blob/master/schema.png)

## myfree
There are two types of objects to be freed: these that belongs to system's malloc and these that were allocated from mymalloc. 
In order to find the kind of the object, we round the address down to a multiple of 4096 and we check if this page corresponds
to a page of our allocator. If the object wasn't allocated by our allocator, then we just call system's free. Otherwise, we 
change the value of the proper bit in the bit vector.
