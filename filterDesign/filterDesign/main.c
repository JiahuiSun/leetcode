#include <stdio.h>
#include <stdlib.h>

//求输入数组长度
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof(x[0]))

/* 以下为Matlab生成的信号和滤波器参数 */
//1kHz和3kHz叠加的波形数据
int sig[] = {0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256,
            0, 256, 0, 256, 0, -256, 0, -256};

//截止频率为2kHz的低通滤波器
int h_1k[] = {0, 0, 0, 1, 0, -1, 0, 2,
            0, -3, 0, 6, 0, -9, 0, 14,
            0, -26, 0, 81, 128, 81, 0, -26,
            0, 14, 0, -9, 0, 6, 0, -3,
            0, 2, 0, -1, 0, 1, 0, 0,
            0};

//截止频率为2KHz的高通滤波器
int h_3k[] = {0, 0, 0, -1, 0, 1, 0, -2,
            0, 3, 0, -6, 0, 9, 0, -14,
            0, 26, 0, -81, 128, -81, 0, 26,
            0, -14, 0, 9, 0, -6, 0, 3,
            0, -2, 0, 1, 0, -1, 0, 0,
            0};

// 卷积函数
int* myConv(int* sig, int sig_len, int* h, int h_len) {
    int *res = (int*)malloc(sizeof(int)*sig_len);
    int tmp;
    
    printf("length of sig is %d\n", sig_len);
    printf("length of h is %d\n", h_len);

    for(int i = 0; i < sig_len; i++) {//反转、平移、相乘相加
        tmp = i;
        res[i] = 0;
        for(int j = 0; j < h_len; j++) {
            if(tmp < 0) break;
            res[i] += sig[tmp]*h[j];
            tmp--;
        }
    }

    return res;
}

int main(int argc, const char * argv[]) {
    int *low_freq_sig, *high_freq_sig;
    
    low_freq_sig = myConv(sig, ARRAY_LENGTH(sig), h_1k, ARRAY_LENGTH(h_1k));
    high_freq_sig = myConv(sig, ARRAY_LENGTH(sig), h_3k, ARRAY_LENGTH(h_3k));
    
    //把结果存起来检验对不对
    FILE *LFS = fopen("./LFS.txt", "w");
    FILE *HFS = fopen("./HFS.txt", "w");
    for(int i = 0; i < ARRAY_LENGTH(sig); i++) {
        fprintf(LFS, "%d, ", low_freq_sig[i]);
        fprintf(HFS, "%d, ", high_freq_sig[i]);
    }
    fclose(LFS);
    fclose(HFS);

    return 0;
}
