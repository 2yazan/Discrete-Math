program Lab4_3;
const 
 n = 10;
type
 t_array =array[1..n] of boolean;
 
function sim_difference(const a,b:t_array):t_array ;
var 
  i:byte;
  c:t_array ;
begin
 for i:=1 to n do
  c[i]:= a[i]<>b[i];
  sim_difference:=c;
end;

function dop_a(const a:t_array):t_array ;
var 
  i:byte;
  c:t_array ;
begin
 for i:=1 to n do
  c[i]:= not a[i];
  dop_a:=c;
end;

function difference(const a,b:t_array):t_array ;
var
  i:byte;
  c:t_array ;
begin
 for i:=1 to n do
  c[i]:= a[i]>b[i];
  difference:=c;
end;

procedure input_array(var a:t_array ; ka:byte);
var 
  i: byte;
begin
 for i:=1 to n do
  a[i]:=false;
 while ka<>0 do
  begin
   read(i);
   a[i]:=true;
   dec(ka);
  end;
end;

procedure output_array(A:t_array );
var 
  i: byte;
begin
 for i:=1 to n do
  if a[i] then
   write(i:4);
   writeln;
end;

var 
  a,b,c,v3,v4:t_array ;
  ka,kb,kc:byte;
begin
  writeln('Enter the number of elements A:');
  readln(ka);
  writeln('Enter the elements of A:');
  input_array(a, ka);
  writeln('Enter the number of elements B:');
  readln(kb);
  writeln('Enter the elements of B:');
  input_array(b, kb);
  writeln('Enter the number of elements C:');
  readln(kc);
  writeln('Enter the elements of C:');
  input_array(c, kc);
  v3 := sim_difference(dop_a(a), c);
  v4 := sim_difference(b, dop_a(a));
  writeln('Result φ^∅:');
  output_array(v3);
  writeln('Result φ^U:');
  output_array(v4);
  writeln('Result not φ^U:');
  v4 := dop_a(sim_difference(b, dop_a(a)));
  output_array(v4);
end.
