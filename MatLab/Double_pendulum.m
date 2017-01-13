clc
clear

syms g;
syms m1 m2;
syms l1 l2;
syms fi1 dfi1 ddfi1;
syms fi2 dfi2 ddfi2;

T=0.5*m1*((dfi1*l1*cos(fi1))^2+(dfi1*l1*sin(fi1))^2)+0.5*m2*((dfi1*l1*cos(fi1)+dfi2*l2*cos(fi2))^2+(dfi1*l1*sin(fi1)+dfi2*l2*sin(fi2))^2);
U=m1*g*l1*cos(fi1)+m2*g*(l1*cos(fi1)+l2*cos(fi2));

L=T-U;

Equations=Lagrange(L,[fi1,dfi1,ddfi1,fi2,dfi2,ddfi2]);
ok1=Equations(1);
ok2=Equations(2);

solf=solve(ok1,ok2,ddfi1,ddfi2);
addfi1=ccode(simplify(solf.ddfi1))
addfi2=ccode(simplify(solf.ddfi2))
