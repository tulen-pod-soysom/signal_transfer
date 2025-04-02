#ifndef WAVHEADER_H
#define WAVHEADER_H

#include <iostream>
#include <fstream>

struct WAVHEADER
{
    // WAV-формат начинается с RIFF-заголовка:

    // Содержит символы "RIFF" в ASCII кодировке
    // (0x52494646 в big-endian представлении)
    char chunkId[4] = {'R','I','F','F'};

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // Это оставшийся размер цепочки, начиная с этой позиции.
    // Иначе говоря, это размер файла - 8, то есть,
    // исключены поля chunkId и chunkSize.
    unsigned int chunkSize;

    // Содержит символы "WAVE"
    // (0x57415645 в big-endian представлении)
    char format[4] = {'W','A','V','E'};

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:

    // Содержит символы "fmt "
    // (0x666d7420 в big-endian представлении)
    char subchunk1Id[4] = {'f','m','t',' '};

    // 16 для формата PCM.
    // Это оставшийся размер подцепочки, начиная с этой позиции.
    unsigned int subchunk1Size = 16;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    unsigned short audioFormat = 1;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    unsigned short numChannels = 1;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    unsigned int sampleRate = 44100;

    // sampleRate * numChannels * bitsPerSample/8
    unsigned int byteRate = sampleRate * 2;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    unsigned short blockAlign = 2;//bitsPerSample/8;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    unsigned short bitsPerSample = 16;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    char subchunk2Id[4] = {'d','a','t','a'};

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    unsigned int subchunk2Size;

    // Далее следуют непосредственно Wav данные.


    std::ofstream& write(std::ofstream& str)
    {
        auto& wh = *this;
        str.write(wh.chunkId, sizeof(wh.chunkId));
        str.write((char*)&wh.chunkSize, sizeof(wh.chunkSize));
        str.write(wh.format, sizeof(wh.format));
        str.write(wh.subchunk1Id, sizeof(wh.subchunk1Id));
        str.write((char*)&wh.subchunk1Size,sizeof(wh.subchunk1Size));
        str.write((char*)&wh.audioFormat,2);
        str.write((char*)&wh.numChannels,2);
        str.write((char*)&wh.sampleRate,4);
        str.write((char*)&wh.byteRate,4);
        str.write((char*)&wh.blockAlign,2);
        str.write((char*)&wh.bitsPerSample,2);
        str.write(wh.subchunk2Id, sizeof(wh.subchunk2Id));
        str.write((char*)&wh.subchunk2Size,4);

        return str;
    }


    WAVHEADER(unsigned numSamples) : subchunk2Size(numSamples * 2), chunkSize(36 + numSamples * 2){}
};

#endif // WAVHEADER_H
