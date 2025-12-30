
    //     int t1 = p.getf(i);
    //     int t2 = p.getf(a[i].b);
    //     int t3 = p.merge(t1, t2);
    //     p.fa[t1] = p.fa[t2] = t3;
    //     a[t2].size += a[t1].size;
    //     a[t2].sum += a[t2].sum;
    //     while(a[t2].sum > m) {
    //         a[t2].sum -= p.del(t2);
    //         a[t2].size--; 
    //     }
    //     ans = max(ans, a[t2].sum * a[t2].size); 
    // }