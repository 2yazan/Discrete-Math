Program lab3_8;
const 
   n = 10;
type 
  t_range = 1..10;
  t_array = array[1..n] of t_range;
  t_base = integer;
  
procedure input_array(var a: t_array; a_n: t_range);
var 
  i: t_range;
begin
 for i := 1 to a_n do
  read(a[i]);
end;

procedure output_array(var a: t_array; a_n: t_range);
var 
  i: t_range;
begin
 for i := 1 to a_n do
  write(a[i],' ');
end;

function check(a: t_array; a_n: t_range; elem: t_base): boolean;
var 
  i: t_range;
begin
 i := 1;
 while (i <= a_n) and (a[i] <> elem) do
  i := i + 1;
  check := (i <= a_n);
end;

function unification(a, b: t_array; var c: t_array; a_n, b_n: t_range): t_range;
var 
  i, k: t_range;
begin
 k := 0;
 for i := 1 to a_n do
  c[i] := a[i];
  k := a_n;
for i := 1 to b_n do
 if not check(a, a_n, b[i]) then
  begin
   k := k + 1;
   c[k] := b[i];
  end;
 unification := k;
end;

function intersection(a, b: t_array; var c: t_array; a_n, b_n: t_range): t_range;
var 
  i, k: t_range;
begin
 k := 0;
 for i := 1 to a_n do
  if check(b, b_n, a[i]) then
   begin
    k := k + 1;
    c[k] := a[i];
   end;
 intersection := k;
end;

function difference(a, b: t_array; var c: t_array; a_n, b_n: t_range): t_range;
var 
  i, k: t_range;
begin
 i := 1;
 while (i <= a_n) and not check(b, b_n, a[i]) do
  begin
   c[i] := a[i];
   i := i + 1;
  end;
 k := i - 1;
 while i <= a_n do
  begin
   if not check(b, b_n, a[i]) then
    begin
     k := k + 1;
     c[k] := a[i];
    end;
   i := i + 1;
  end;
 difference := k;
end;

function sim_difference(a, b: t_array; var c: t_array; a_n, b_n: t_range): t_range;
var 
  d1, d2: t_array;
  i, k1, k2: t_range;
begin
 k1 := difference(a, b, d1, a_n, b_n);
 k2 := difference(b, a, d2, b_n, a_n);
 for i := 1 to k1 do
  c[i] := d1[i];
 for i := 1 to k2 do
  c[k1+i] := d2[i];
 sim_difference := k1 + k2;
end;

function f3_value(a, b, c: t_array; var f3: t_array; a_n, b_n, c_n: t_range): t_range;
var
  t1, t2, t3, t4, t5, t6, t7, t8: t_array;
  k1, k2, k3, k4, k5, k6, k7, k8: t_range;
begin
 k1:= difference(a,b,t1,a_n,b_n);
 k2:= difference(t1,c,t2,k1,c_n);
 k3:= difference(b,a,t3,b_n,a_n);
 k4:= difference(t3,c,t4,k3,c_n);
 k5:= difference(c,a,t5,c_n,a_n);
 k6:= difference(t5,b,t6,k5,b_n);
 k7:= unification(t2, t4, t7, k2, k4);
 f3_value := unification(t7, t6, f3, k7, k6);
 
end;

function f4_value(a, b, c: t_array; var f4: t_array; a_n, b_n, c_n: t_range): t_range;
var
  t1, t2, t3, t4, t5, t6, t7: t_array;
  k1, k2, k3, k4, k5, k6, k7: t_range;
begin
 k1:= unification(b,c,t1,b_n,c_n);
 k2:= unification(a,c,t2,a_n,c_n);
 k3:= unification(a,b,t3,a_n,b_n);
 k4:= difference(a,t1,t4,a_n,k1);
 k5:= difference(b,t2,t5,b_n,k2);
 k6:= difference(c,t3,t6,c_n,k3);
 k7:= unification(t4, t5, t7, k4, k5);
 f4_value := unification(t7, t6, f4, k7, k6);
end;

procedure ravno(f3, f4: t_array; var f3_n, f4_n: t_range);
var
  i,j:t_range;
  b:boolean;
begin
  for i:=1 to f3_n do
    for j:=1 to f4_n do
      begin
       if f3[i] = f4[j] then
         b:=true;
      end;
  if b=true then
    write('ravno')
  else
    write('ne ravno');
end;

var 
  a, b, c, f3, f4: t_array;
  a_n, b_n, c_n, f3_n, f4_n: t_range;
begin
  writeln('Enter the number of elements A:');
  readln(a_n);
  writeln('Enter the elements of A:');
  input_array(a, a_n);
  writeln('Enter the number of elements B:');
  readln(b_n);
  writeln('Enter the elements of B:');
  input_array(b, b_n);
  writeln('Enter the number of elements C:');
  readln(c_n);
  writeln('Enter the elements of C:');
  input_array(c, c_n);
  
  writeln;
  f3_n := f3_value(a, b, c, f3, a_n, b_n, c_n);
  write('f3 = ');
  output_array(f3, f3_n);
  writeln;
  
  f4_n := f4_value(a, b, c, f4, a_n, b_n, c_n);
  write('f4 = ');
  output_array(f4, f4_n);
  writeln;
  
  ravno(f3, f4, f3_n, f4_n);
end.
