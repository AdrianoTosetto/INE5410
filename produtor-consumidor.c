#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

void print_buffer();

const uint8_t buffer_size = 5;

uint8_t produce_i = 0;
uint8_t consume_i = 0;

uint8_t count = 0;

int buffer[] = {0,0,0,0,0};

bool producer_sleeping = false;
bool consumer_sleeping  = false;

/*only produces 1*/

void *produce(void *arg){
  while(1){
	 if(!producer_sleeping){
	    produce_i = (produce_i + 1) % buffer_size;
		  buffer[produce_i] = buffer[produce_i] == 0?1:0;
		  count++;
		  if(count == buffer_size) producer_sleeping = true;
		  if(count == 1) consumer_sleeping = false;
	   	print_buffer();
	    if(producer_sleeping && consumer_sleeping) printf("Consumidor e produtor estao dormindo\n");
	    //sleep(1);
	  }
  }
}

void *consume(void *arg){
  while(1){
	    if(!consumer_sleeping){
		    consume_i = (consume_i + 1) % buffer_size;	
		    buffer[consume_i] = buffer[consume_i] == 1?0:1;
		    count--;
		    if(count == 0) consumer_sleeping = true;
		    if(count == buffer_size - 1) producer_sleeping = false;
		    print_buffer();
		    if(producer_sleeping && consumer_sleeping) printf("Consumidor e produtor estao dormindo\n");
		    //sleep(1);
    }
  }
}

void print_buffer(){
    printf("%d %d %d %d %d\n",buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
}

int main(int argc, char **argv){

  pthread_t t_consumidora, t_produtora;
  pthread_create(&t_consumidora, NULL, produce, NULL);
  pthread_create(&t_produtora, NULL, consume, NULL); 
  
  pthread_join(t_consumidora, NULL);
  pthread_join(t_produtora, NULL);
  return 0;
}
