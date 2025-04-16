#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int isPagePresent(int frames[], int num_frames, int page) 
{
    for (int i = 0; i < num_frames; i++) 
    {
        if (frames[i] == page) 
        {
            return 1;
        }
    }
    return 0;
}

int findLFU(int freq[], int num_frames, int time[], int counter) 
{
    int min_freq = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < num_frames; i++) 
    {
        if (freq[i] < min_freq) 
        {
            min_freq = freq[i];
            min_index = i;
        }
        else if (freq[i] == min_freq && time[i] < time[min_index])
        {
            min_index = i;
        }
    }
    return min_index;
}


void lfuPageReplacement(int pages[], int num_pages, int num_frames) {
    int frames[num_frames];
    int freq[num_frames]; 
    int time[num_frames]; 
    int page_faults = 0;
    int counter = 0; 
    for (int i = 0; i < num_frames; i++) 
    {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }
    printf("Page Reference String ");
    for (int i = 0; i < num_pages; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n\n");
    printf("Step\tPage\tFrames\t\tFrequencies\tPage Fault\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < num_pages; i++) 
    {
        int current_page = pages[i];
        printf("%d\t%d\t", i+1, current_page);
        
        if (!isPagePresent(frames, num_frames, current_page)) 
        {
            int pos;
            if (counter < num_frames) 
            {
                pos = counter; 
            } 
            else 
            {
                pos = findLFU(freq, num_frames, time, counter);
            }
            frames[pos] = current_page;
            freq[pos] = 1;
            time[pos] = ++counter;
            page_faults++;
            for (int j = 0; j < num_frames; j++) 
            {
                if (frames[j] != -1) 
                {
                    printf("%d ", frames[j]);
                } 
                else 
                {
                    printf("- ");
                }
            }
            printf("\t");
            for (int j = 0; j < num_frames; j++) 
            {
                printf("%d ", freq[j]);
            }
            printf("\t\tYes\n");
        } 
        else 
        {
            for (int j = 0; j < num_frames; j++)
            {
                if (frames[j] == current_page)
                {
                    freq[j]++;
                    time[j] = ++counter;
                    break;
                }
            }
            for (int j = 0; j < num_frames; j++) 
            {
                if (frames[j] != -1) 
                {
                    printf("%d ", frames[j]);
                } 
                else 
                {
                    printf("- ");
                }
            }
            printf("\t");
            for (int j = 0; j < num_frames; j++) 
            {
                printf("%d ", freq[j]);
            }
            printf("\t\tNo\n");
        }
    }
    printf("\nTotal Page Faults %d\n", page_faults);
    printf("Page Fault Rate %.2f%%\n", (float)page_faults / num_pages * 100);
}

int main() 
{
    int num_pages, num_frames;
    printf("Enter the number of pages in the reference string ");
    scanf("%d", &num_pages);
    int pages[num_pages];
    printf("Enter the page reference string ");
    for (int i = 0; i < num_pages; i++) 
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames ");
    scanf("%d", &num_frames);
    lfuPageReplacement(pages, num_pages, num_frames);
    return 0;
}
