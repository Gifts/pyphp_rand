<?PHP

for ($i=0; $i<10000000; ++$i)
{
    mt_srand($i);
    mt_rand();
}

echo mt_rand();
