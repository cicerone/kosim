#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstdio>

#include <boost/interprocess/sync/interprocess_mutex.hpp>

struct shared_memory_log
{
   enum { NumItems = 100 };
   enum { LineSize = 100 };

   shared_memory_log()
      :  current_line(0)
      ,  end_a(false)
      ,  end_b(false)
   {}

   //Mutex to protect access to the queue
   boost::interprocess::interprocess_mutex mutex;

   //Items to fill
   char   items[NumItems][LineSize];
   int    current_line;
   bool   end_a;
   bool   end_b;
};


using namespace boost::interprocess;

int main ()
{
   //Remove shared memory on destruction
   struct shm_remove
   {
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   } remover;

   //Open the shared memory object.
   shared_memory_object shm
      (open_only                    //only create
      ,"MySharedMemory"              //name
      ,read_write  //read-write mode
      );

   //Map the whole shared memory in this process
   mapped_region region
      (shm                       //What to map
      ,read_write //Map it as read-write
      );

   //Get the address of the mapped region
   void * addr       = region.get_address();

   //Construct the shared structure in memory
   shared_memory_log * data = static_cast<shared_memory_log*>(addr);

   //Write some logs
   for(int i = 0; i < 100; ++i){
      //Lock the mutex
      scoped_lock<interprocess_mutex> lock(data->mutex);
      std::sprintf(data->items[(data->current_line++) % shared_memory_log::NumItems]
               ,"%s_%d", "process_b", i);
      if(i == (shared_memory_log::NumItems-1))
         data->end_b = true;
      //Mutex is released here
   }

   //Wait until the other process ends
   while(1){
      scoped_lock<interprocess_mutex> lock(data->mutex);
      if(data->end_a)
         break;
   }
   return 0;
}

