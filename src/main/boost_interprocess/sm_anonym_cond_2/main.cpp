#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstring>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

struct trace_queue
{
   enum { LineSize = 100 };

   trace_queue()
      :  message_in(false)
   {}

   //Mutex to protect access to the queue
   boost::interprocess::interprocess_mutex      mutex;

   //Condition to wait when the queue is empty
   boost::interprocess::interprocess_condition  cond_empty;

   //Condition to wait when the queue is full
   boost::interprocess::interprocess_condition  cond_full;

   //Items to fill
   char   items[LineSize];

   //Is there any message
   bool message_in;
};


using namespace boost::interprocess;

int main ()
{
   //Create a shared memory object.
   shared_memory_object shm
      (open_only                    //only create
      ,"shared_memory"              //name
      ,read_write                   //read-write mode
      );

   try{
      //Map the whole shared memory in this process
      mapped_region region
         (shm                       //What to map
         ,read_write //Map it as read-write
         );

      //Get the address of the mapped region
      void * addr       = region.get_address();

      //Obtain a pointer to the shared structure
      trace_queue * data = static_cast<trace_queue*>(addr);

      //Print messages until the other process marks the end
      bool end_loop = false;
      do{
         scoped_lock<interprocess_mutex> lock(data->mutex);
         if(!data->message_in){
            data->cond_empty.wait(lock);
         }
         if(std::strcmp(data->items, "last message") == 0){
            end_loop = true;
         }
         else{
            //Print the message
            std::cout << data->items << std::endl;
            //Notify the other process that the buffer is empty
            data->message_in = false;
            data->cond_full.notify_one();
         }
//         sleep(1);
      }
      while(!end_loop);
   }
   catch(interprocess_exception &ex){
      shared_memory_object::remove("shared_memory");
      std::cout << ex.what() << std::endl;
      return 1;
   }

   //Erase shared memory
   shared_memory_object::remove("shared_memory");
   return 0;
}

