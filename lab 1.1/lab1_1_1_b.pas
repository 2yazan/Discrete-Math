Program lab1_1_1_b;
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
    write(a[i],' ');
end;

function count_elem(a, b: t_arr; a_n, b_n: t_range): t_range;
var i, j, k: t_range;
begin
  j := 1;
  k := 0;
  for i := 1 to a_n do
    begin
      while (j <= b_n) and (a[i] >= b[j]) do
        begin
          if a[i] = b[j] then
            begin
              k := k + 1;
            end;
            j := j + 1;
        end;
    end;
  count_elem := k;
end;

{Inclusion}
function inclusion(a, b: t_arr; a_n, b_n: t_range): boolean;
begin
  inclusion := (a_n <= b_n) and (count_elem(a, b, a_n, b_n) = a_n);
end;

{Strict Inclusion}
function strong_inclusion(a, b: t_arr; a_n, b_n: t_range): boolean;
begin
  strong_inclusion := (a_n < b_n) and (count_elem(a, b, a_n, b_n) = a_n);
end;

{Union}
function unification(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, j, k: t_range;
begin
  i := 1;
  j := 1;
  k := 1;
  while (i <= a_n) and (j <= b_n) do
  begin
    if a[i] < b[j] then
    begin
      c[k] := a[i];
      i := i + 1;
    end
    else if a[i] > b[j] then
    begin
      c[k] := b[j];
      j := j + 1;
    end
    else
    begin
      c[k] := b[j];
      j := j + 1;
      i := i + 1;
    end;
    k := k + 1;
  end;
  while i <= a_n do
  begin
    c[k] := a[i];
    i := i + 1;
    k := k + 1;
  end;
  while j <= b_n do
  begin
    c[k] := b[j];
    j := j + 1;
    k := k + 1;
  end;
  unification := k - 1;
end;

{Intersection}
function intersection(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, j, k: t_range;
begin
  j := 1;
  k := 0;
  for i := 1 to a_n do
  begin
    while (j <= b_n) and (a[i] >= b[j]) do
    begin
      if a[i] = b[j] then
      begin
        k := k + 1;
        c[k] := b[j];
      end;
      j := j + 1;
    end;
  end;
  intersection := k;
end;

{Difference}
function difference(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, j, k: t_range;
begin
  j := 1;
  k := 0;
  for i := 1 to b_n do
  begin
    while (j <= a_n) and (a[j] <= b[i]) do
    begin
      if a[j] <> b[i] then
      begin
        k := k + 1;
        c[k] := a[j];
      end;
      j := j + 1;
    end;
  end;
  while j <= a_n do
  begin
    k := k + 1;
    c[k] := a[j];
    j := j + 1;
  end;
  difference := k;
end;

{Symmetric Difference}
function sym_difference(a, b: t_arr; var c: t_arr; a_n, b_n: t_range): t_range;
var i, j, k: t_range;
begin
  i := 1;
  j := 1;
  k := 1;
  while (i <= a_n) and (j <= b_n) do
  begin
    if a[i] < b[j] then
    begin
      c[k] := a[i];
      i := i + 1;
      k := k + 1;
    end
    else if a[i] > b[j] then
    begin
      c[k] := b[j];
      j := j + 1;
      k := k + 1;
    end
    else
    begin
      j := j + 1;
      i := i + 1;
    end;
  end;
  while i <= a_n do
  begin
    c[k] := a[i];
    i := i + 1;
    k := k + 1;
  end;
  while j <= b_n do
  begin
    c[k] := b[j];
    j := j + 1;
    k := k + 1;
  end;
  sym_difference := k - 1;
end;

{Дополнение до универсума} 
function extension(a: t_arr; var e: t_arr; a_n: t_range): integer;
var i, j, k: integer;
begin
  i := 1;
  j := 1;
  k := 0;
  while (i <= N) and (j <= a_n) do
  begin
    if a[j] = i then
    begin
      i := i + 1;
      j := j + 1;
    end
    else if i > a[j] then
      j := j + 1
    else
    begin
      k := k + 1;
      e[k] := i;
      i := i + 1;
    end;
  end;
  while i <= N do
  begin
    k := k + 1;
    e[k] := i;
    i := i + 1;
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
  writeln('Enter the number of elements A and the elements themselves');
  readln(a_n);
  input_arr(a, a_n);
  writeln('Enter the number of elements B and the elements themselves');
  readln(b_n);
  input_arr(b, b_n);
  writeln('Enter the number of elements C and the elements themselves');
  readln(c_n);
  input_arr(c, c_n);
  d_n := solve_d(a, b, c, d, a_n, b_n, c_n);
  output_arr(d, d_n);
end.
