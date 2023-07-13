\* PROGRAMMA *\
program lecticos
{ declare x,y,z
  enddeclare
  procedure p(inout a,in k)
  { declare b enddeclare
    function fp(in r)
	{ declare ta,ma enddeclare
	  ma:=r-1;
	  ta:=6*ma;
	  return(ta)
	}
    while (a>=10-4*9+111)
    { b:=a-9999;
      a:=k+6
    };
    if (not[[b<0 and [k>3 or k<1]]])
      a:=k+10
	else
	{ a:=k;
	  b:=a-6;
	};
    a:=k-44
  }
  function f(copy u,in s,inout t)
  { declare g,v enddeclare
    procedure pf(inout x,copy y)
	{ x:=y+2/9;
	  y:=6*x;
	}
	g:=u+2*s;
    v:=g-6;
	forcase
    {  when(g=55)
       {  t:=g;
	      v:=v+1;
	   }
	   when(v<>7)
       {  v:=v-1;
	   }
    };
	incase
    {  when(g=55)
       {  t:=g;
	      v:=v+1;
	   }
	   when(v<>7)
       {  v:=v-1;
	   }
    };
    do
    {  t:=g;
       v:=v+1;
    }while(v<=0);
	return(t)
  }
  x:=f(copy y,in 7,inout z);
  call p(inout x,in 8135)
}

