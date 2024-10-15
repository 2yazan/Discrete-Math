Program lab1_1_1_a;
const N = 10;
type t_range = 1..10;
  t_arr = array[1..N] of t_range;
  t_base = integer;

procedure input_arr(var a: t_arr; a_n: t_range);
var i: t_range;
begin
  for i := 1 to a_n do
    read(a[i]);
end;

procedure output_arr(var a: t_arr; a_n: t_range);
var i: t_range;
begin
  for i := 1 to a_n do
    write(a[i], ' ');
end;

{Check if an element is present in array 'a' of size 'a_n'}
function check_elem(a: t_arr; a_n: t_range; elem: t_base): boolean;
var i: t_range;
begin
  i := 1;
  while (i <= a_n) and (a[i] <> elem) do
    i := i + 1;
  check_elem := (i <= a_n);
end;

{Inclusion}
function inclusion(a, b: t_arr; a_n, b_n: t_range): boolean;
var i: t_range;
begin
  i := 1;
  while (i <= a_n) and check_elem(b, b_n, a[i]) do
    i := i + 1;
  inclusion := i > a_n;
end;

{Strict Inclusion}
function strong_inclusion(a, b: t_arr; a_n, b_n: t_range): boolean;
var i: t_range;
begin
  if (a_n > 0) and (a_n <> b_n) then
  begin
    i := 1;
    while (i <= a_n) and check_elem(b, b_n, a[i]) do
      i := i + 1;
    strong_inclusion := i > a_n;
  end
  else strong_inclusion := false;
end;

{Union}
function unification(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, k: t_range;
begin
  k := 0;
  for i := 1 to a_n do
    c[i] := a[i];
  k := a_n;
  for i := 1 to b_n do
    if not check_elem(a, a_n, b[i]) then
    begin
      k := k + 1;
      c[k] := b[i];
    end;
  unification := k;
end;

{Intersection}
function intersection(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, k: t_range;
begin
  k := 0;
  for i := 1 to a_n do
    if check_elem(b, b_n, a[i]) then
    begin
      k := k + 1;
      c[k] := a[i];
    end;
  intersection := k;
end;

{Difference}
function difference(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, k: t_range;
begin
  i := 1;
  while (i <= a_n) and not check_elem(b, b_n, a[i]) do
  begin
    c[i] := a[i];
    i := i + 1;
  end;
  k := i - 1;
  while i <= a_n do
  begin
    if not check_elem(b, b_n, a[i]) then
    begin
      k := k + 1;
      c[k] := a[i];
    end;
    i := i + 1;
  end;
  difference := k;
end;

{Symmetric difference}
function sym_difference(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var d1, d2: t_arr;
i, k1, k2: t_range;
begin
  k1 := difference(a, b, d1, a_n, b_n);
  k2 := difference(b, a, d2, b_n, a_n);
  for i := 1 to k1 do
    c[i] := d1[i];
  for i := 1 to k2 do
    c[k1 + i] := d2[i];
  sym_difference := k1 + k2;
end;

{Complement to the universe}
function extension(a: t_arr; var e: t_arr; a_n: t_range): integer;
var i, k: integer;
begin
  k := 0;
  for i := 1 to N do
    if not check_elem(a, a_n, i) then
    begin
      k := k + 1;
      e[k] := i;
    end;
  extension := k;
end;

function solve_d(a, b, c: t_arr; var d: t_arr; a_n, b_n, c_n: t_range): t_range;
var t1, t2, t3, t4, t5: t_arr;
k1, k2, k3, k4, k5: t_range;
begin
  k1 := sym_difference(b, c, t1, b_n, c_n);
  k2 := unification(b, c, t2, b_n, c_n);
  k3 := difference(a, t1, t3, a_n, k1);
  k4 := difference(t2, a, t4, k2, a_n);
  solve_d := unification(t3, t4, d, k3, k4);
end;

var a, b, c, d: t_arr;
a_n, b_n, c_n, d_n: t_range;
begin
  writeln('Enter the number of elements for A and the elements themselves');
  readln(a_n);
  input_arr(a, a_n);
  writeln('Enter the number of elements for B and the elements themselves');
  readln(b_n);
  input_arr(b, b_n);
  writeln('Enter the number of elements for C and the elements themselves');
  readln(c_n);
  input_arr(c, c_n);
  d_n := solve_d(a, b, c, d, a_n, b_n, c_n);
  output_arr(d, d_n);
end.
