[top]
components : inquiry
components : laboratory
components : diagnosis 
components : operation
out : out
in : in
Link : in in@inquiry
Link : out@inquiry in@laboratory
Link : out@laboratory  in@diagnosis 
Link : out@diagnosis in@operation
Link : out@operation out

[inquiry]
components : queue1@MSQueue
components : nurse@Server
out : out
in : in  
Link : in in@queue1
Link : ready@nurse next@queue1
Link : out@queue1 in@nurse
Link : out@nurse out

[queue1]
preparation : 00:00:05:000 

[nurse]
distribution : normal
mean : 2
deviation : 1

[laboratory]
components : queue2@MSQueue
components : lab@Server
out : out
in : in  
Link : in in@queue2
Link : ready@lab next@queue2
Link : out@queue2  in@lab
Link : out@lab out

[queue2]
preparation : 00:00:05:000 

[lab]
distribution : normal
mean : 2
deviation : 1

[diagnosis]
components : queue3@MSQueue
components : doctor@Server
out : out
in : in  
Link : in in@queue3
Link : ready@doctor next@queue3
Link : out@queue3 in@doctor
Link : out@doctor out

[queue3]
preparation : 00:00:05:000 

[doctor]
distribution : normal
mean : 2
deviation : 1

[operation]
components : queue4@MSQueue
components : surgeon@Server
out : out
in : in  
Link : in in@queue4
Link : ready@doctor next@queue3
Link : out@queue4 in@surgeon
Link : out@surgeon out

[queue4]
preparation : 00:00:05:000 

[surgeon]
distribution : normal
mean : 2
deviation : 1







