clear all;clc;
delete(instrfindall)
s1=serial('COM4','BaudRate',115200);
s2=serial('COM16','BaudRate',115200);
fopen(s1);
fopen(s2);
while (1)
    x=str2num(fscanf(s1));
    fprintf(s2,'%d\n',x');
end
fclose(s2);
fclose(s1);
delete(instrfindall);