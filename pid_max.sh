#!/bin/bash

#Write a shell script that prints the maximum value a process ID can be

path=/proc/sys/kernel/pid_max

cat $path
