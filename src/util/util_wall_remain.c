/*
 $Id: util_wall_remain.c,v 1.11 2002-10-18 01:39:03 edo Exp $
*/
#include <stdio.h>
#include "typesf2c.h"

#if defined(CRAY) || defined(CRAY_T3D) || defined(CRAY_T3E) || defined(USE_FCD)
#define util_batch_job_time_remaining_ UTIL_BATCH_JOB_TIME_REMAINING
#endif

#define NOT_AVAILABLE -1

/* util_batch_job_time_remaining returns the wall time (>=0) in seconds
   remaining for job execution, or -1 if no information is available */

#if (defined(SP1) && defined(JOBTIMEPATH)) || defined(LSF)
#define DONEIT 1  

#include <unistd.h>
#include <sys/wait.h>

Integer FATR util_batch_job_time_remaining_(void)
{
  FILE *p;
  char cmd[1024];
  int t, status;

#ifdef LSF
  sprintf(cmd,"%s/jobtime_lsf",JOBTIMEPATH);
#else
  sprintf(cmd,"%s/jobtime",JOBTIMEPATH);
#endif

  if (access(cmd,F_OK|X_OK)) {	/* If cannot access perl script */
    /*(void) fprintf(stderr,"ujtr: cannot access %s\n",cmd);*/
    return NOT_AVAILABLE;
  }

  if (!(p = popen(cmd,"r"))) {
    /*(void) fprintf(stderr,"ujtr: popen %s failed\n",cmd);*/
    return NOT_AVAILABLE;
  }
  
  if (fscanf(p,"%d",&t) != 1) {
    /*(void) fprintf(stderr,"ujtr: failed to read time from pipe\n");*/
    (void) fclose(p);
    (void) wait(&status);
    return NOT_AVAILABLE;
  }

  (void) fclose(p);
  (void) wait(&status);

  if (t < 0) t = 0;

  return t;
}

#endif


#ifndef DONEIT
Integer FATR util_batch_job_time_remaining_(void)
{
  return NOT_AVAILABLE;
}
#endif
