function [M]=Lagrange(Lag,V)
syms t;
Var=length(V)/3;
Vt=V;
    for cont0=1:1:Var
        Vt(cont0*3-2)=strcat('f',num2str(cont0),'(t)');
        Vt(cont0*3-1)=diff(Vt((cont0*3)-2),t);
        Vt(cont0*3)=diff(Vt((cont0*3)-2),t,2);
    end
    for cont0=1:1:Var
        L1=simplify(diff(Lag,V(cont0*3-1)));
        L2=simplify(diff(Lag,V(cont0*3-2)));
        Dposx=L1;

        for cont=1:1:Var*3         
             Dposx=subs(Dposx,V(cont),Vt(cont));
        end
        L1=diff(Dposx,t);

        for cont=Var*3:-1:1         
             L1=subs(L1,Vt(cont),V(cont));
        end
        L1F=L1-L2;
        L1F=simplify(expand(L1F));
        L1F=collect(L1F,Vt(cont0*3));
        M(cont0)=L1F;
    end
end
