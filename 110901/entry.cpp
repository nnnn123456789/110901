#include <cstdio>
#include <cstdlib>
#include <cstring>
#pragma warning(disable:4996)
#pragma pack(1)

struct sound
{
    char f;
    char m;
};

unsigned int frefromsound(sound s)
{
    int p = 1;
loops:
    static unsigned int low[] = {262, 294, 330, 349, 392, 440, 494};
    if (1 == s.f)
    {
        return p * low[s.m - 1];
    }
    else
    {
        s.f -= 1;
        p *= 2;
        goto loops;
    }
}

int main(int argc, char* argv[])
{
    FILE * fp;

    if (1 == argc)
    {
        printf("参数错误!\n");
        printf("尝试输入 /? 获取帮助\n");
        system("pause>nul");
        return 1;
    }
    else if (2 == argc)
    {
        if (0 == (strcmp(argv[1], "/?")) || 0 == strcmp(argv[1], "\\?"))
        {
            printf("\n\n");
            printf("参数: /default|/?|FileName");
            printf("\n\n");
            printf("      打开文件名为 FileName 的文档并按指定规则播放声音");
            printf("\n");
            printf("      /?        -  打开帮助页面\n");
            printf("      /default  -  读取默认文件: myfavarite.dat\n\n\n");
            printf("        developed by Yuan     \n\n\n");
            system("pause>nul");
            return 1;
        }
        else if ((0 == strcmp(argv[1], "/default")) || 0 == strcmp(argv[1], "\\default"))
        {
            fp = fopen("myfavarite.dat", "rb");
        }
        else if ((0 == strcmp(argv[1], "吐槽")))
        {
            printf("谁知道老师留这个奇葩作业\n");
            printf("一个文件, 难道不应该前两个字符是标识符的吗?!\n");
            printf("同一个音节的信息居然不存在一起\n");
            printf("别人说这个歌叫<<沧海一声笑>>, 反正我听了几遍没听出来=_=!\n");
            printf("我觉得老师看不到这句话的, 老师应该没兴趣反汇编我的东西才对\n");
            printf("感谢你看到这句话!\n");
            system("pause>nul");
            return 233;
        }
        else
        {
            fp = fopen(argv[1], "rb");
        }
    }
    else
    {
        printf("参数错误, 请重试!\n\n");
        system("pause>nul");
        return 3;
    }
        
    if (nullptr == fp)
    {
        printf("error!\n\n");
        system("pause>nul");
        return -1;
    }
    int d[2];
    int &n = d[0], &t = d[1];
    fread(d, sizeof(int), 2, fp);
    sound* ps;
    ps = static_cast<sound*>(malloc(n * sizeof(sound)));
    if (nullptr == ps)
    {
        printf("memory error\n");
        fclose(fp);
        system("pause>nul");
        return -2;
    }
    fread(ps, sizeof(sound), n, fp);
    unsigned char * pl;
    pl = static_cast<unsigned char*>(malloc(n * sizeof(unsigned char)));
    if (nullptr == pl)
    {
        printf("memory error\n");
        fclose(fp);
        free(ps);
        system("pause>nul");
        return -2;
    }
    fread(pl, sizeof(unsigned char), n, fp);
    fclose(fp);
    for (int i = 0; i < n; i++)
    {
        int k = frefromsound(ps[i]);
        _beep(k, t * static_cast<unsigned int>(pl[i]));
    }
    free(ps);
    free(pl);
    system("pause");
    return 0;
}