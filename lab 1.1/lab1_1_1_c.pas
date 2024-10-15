Program lab1_1_1_c;
const N = 10;
type t_range = 1..10;
t_arr = array[1..N] of boolean;

procedure input_arr(var a: t_arr; a_n: t_range);
var i, j: t_range;
begin
  for i := 1 to a_n do
    a[i] := false;
  for i := 1 to a_n do
  begin
    read(j);
    a[j] := true;
  end;
end;

procedure output_arr(var A: t_arr);
var i: t_range;
begin
  for i := 1 to N do
    if (A[i] = true) then
      write(i, ' ');
end;

{check the equality of two boolean arrays from position i}
function equality(a, b: t_arr; i: t_range): boolean;
begin
  while (i <= N) and (a[i] = b[i]) do
    i := i + 1;
  equality := i > N;
end;

{Inclusion}
function inclusion(a, b: t_arr): boolean;
var i: t_range;
begin
  i := 1;
  while (i <= N) and ((not a[i] or (a[i] = b[i]))) do
    i := i + 1;
  inclusion := i > N;
end;

{Strict Inclusion}
function strong_inclusion(a, b: t_arr): boolean;
var i: t_range;
    flag: boolean;
begin
  flag := false;
  i := 1;
  while (i <= N) and not (a[i]) do
    i := i + 1;
  flag := (i > N);
  if not (equality(a, b, i) or flag) then
  begin
    i := 1;
    while (i <= N) and (not a[i] or (a[i] = b[i])) do
      i := i + 1;
    strong_inclusion := i > N;
  end
  else 
    strong_inclusion := false;
end;

{Union}
procedure unification(a, b: t_arr; var c: t_arr);
var i: t_range;
begin
  for i := 1 to N do
    c[i] := a[i] or b[i];
end;

{Intersection} 
procedure intersection(a, b: t_arr; var c: t_arr);
var i: t_range;
begin
  for i := 1 to N do
    c[i] := a[i] and b[i];
end;

{Difference}
procedure difference(a, b: t_arr; var c: t_arr);
var i: t_range;
begin
  for i := 1 to N do
    c[i] := (a[i] and not b[i]);
end;

{Symmetric difference}
procedure sym_difference(a, b: t_arr; var c: t_arr);
var i: t_range;
begin
  for i := 1 to N do
    c[i] := (a[i] xor b[i]);
end;

{Complement to the universe:} 
procedure extension(a: t_arr; var e: t_arr);
var i: word;
begin
  for i := 1 to N do
    e[i] := not a[i];
end;

procedure solve_d(a, b, c: t_arr; var d: t_arr; a_n, b_n, c_n: t_range);
var t1, t2, t3, t4: t_arr;
begin
  sym_difference(b, c, t1);
  unification(b, c, t2);
  difference(a, t1, t3);
  difference(t2, a, t4);
  unification(t3, t4, d);
end;

var a, b, c, d: t_arr;
a_n, b_n, c_n: t_range;
begin
  writeln('Enter the number of elements A and the elements themselves');
  readln(a_n);
  input_arr(a, a_n);
  writeln('Enter the number of elements B and the elements themselves');
  readln(b_n);
  input_arr(b, b_n);
  writeln('Enter the number of elements C and the elements themselves');
  readln(c_n);
  input_arr(c, c_n);
  solve_d(a, b, c, d, a_n, b_n, c_n);
  writeln('The result is:');
  output_arr(d);
end.
