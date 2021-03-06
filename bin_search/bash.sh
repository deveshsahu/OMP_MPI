#!/bin/bash 	 
#$ -V 	#Inherit the submission environment
#$ -cwd 	# Start job in submission directory
#$ -N myMPI 	# Job Name
#$ -j y 	# Combine stderr and stdout
#$ -o $JOB_NAME.o$JOB_ID 	# Name of the output file (eg. myMPI.oJobID)
#$ -pe 2way 4 	# Requests 12 tasks/node, 24 cores total
#$ -q normal 	# Queue name normal
#$ -l h_rt=01:30:00 	# Run time (hh:mm:ss) - 1.5 hours
#$ -m be 	# Email at Begin and End of job
set -x 	# Echo commands, use set echo with csh
ibrun ./combo.out 	# Run the MPI executable named a.out
