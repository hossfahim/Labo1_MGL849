#include "humidity.h"
#include "pressure.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

void gestsigal1()
{
	printf("Temp (from pressure) = %.1f°C\n",temperature());
	printf("\n");
	
}

void gestsigal2()
{
	printf("Humidity = %.0f%% rH\n",humidity());
	printf("\n");
}

void gestsigal3()
{
	printf("Pressure = %.0f hPa\n", pressure());
	printf("\n");
}


int main (void){


	timer_t timer_1, timer_2, timer_3;
	struct sigevent event_1, event_2, event_3;
	struct itimerspec spec_1, spec_2, spec_3;

	// Capturer les trois signaux 
	signal(SIGRTMIN+1, gestsigal1);
	signal(SIGRTMIN+2, gestsigal2);
	signal(SIGRTMIN+3, gestsigal3);

	// Configuraiton de la notification
	event_1.sigev_notify = SIGEV_SIGNAL;
	event_1.sigev_signo  = SIGRTMIN+1;

	// Configuration de la periode du timer 1
	spec_1.it_interval.tv_sec  = 1;
	spec_1.it_interval.tv_nsec = 0;
	spec_1.it_value = spec_1.it_interval;

	// Creation du timer
	if (timer_create(CLOCK_REALTIME, & event_1, & timer_1) != 0) {
		printf("Erreur dans la creation du timer #1");
		exit(EXIT_FAILURE);
	}

	// Congiguratione et creation du timer 2
	event_2.sigev_notify = SIGEV_SIGNAL;
	event_2.sigev_signo  = SIGRTMIN+2;
	spec_2.it_interval.tv_sec  = 1;
	spec_2.it_interval.tv_nsec = 0; 
	spec_2.it_value = spec_2.it_interval;
	if (timer_create(CLOCK_REALTIME, & event_2, & timer_2) != 0) {
		printf("Erreur dans la creation du timer #2");
		exit(EXIT_FAILURE);
	}
	// Congiguratione et creation du timer 3
	event_3.sigev_notify = SIGEV_SIGNAL;
	event_3.sigev_signo  = SIGRTMIN+3;
	spec_3.it_interval.tv_sec  = 1;
	spec_3.it_interval.tv_nsec = 0; 
	spec_3.it_value = spec_3.it_interval;
	if (timer_create(CLOCK_REALTIME, & event_3, & timer_3) != 0) {
		printf("Erreur dans la creation du timer #3");
		exit(EXIT_FAILURE);
	}

	// Programmer les timers
	if ((timer_settime(timer_1, 0, &spec_1, NULL) != 0)
	 || (timer_settime(timer_2, 0, &spec_2, NULL) != 0)
	 || (timer_settime(timer_3, 0, &spec_3, NULL) != 0)) {
		printf("Erreur dans la programmation des timers");
		exit(EXIT_FAILURE);
	}
	

		while (1)
		pause();
	return EXIT_SUCCESS;

	
}
