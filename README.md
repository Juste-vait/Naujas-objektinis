v3.0

Realokacijų skaičius vienodas std::vector ir Vector klasei:
![31D1F6D8-3132-4675-B0C9-5E1F9D61933A_4_5005_c](https://github.com/user-attachments/assets/fd514389-8109-4b25-92b7-52d82a512261)


Atlikti std::vector vs Vector testai, užpildant vektorius 10000, 100000, 1000000, 10000000, 100000000 elementų push_back() funkcija. Pagal visus testus ir jų vidurkį, greičiau užpildomas naujai sukurtas Vector klasės vektorius.
![9BC0F310-E42E-4E0F-BE85-7D4E772C701E](https://github.com/user-attachments/assets/1a076f90-51f0-493e-9b5b-043cdde4fd6c)



![52EAE185-7E83-4D81-8DDD-B4D9FB80B05E_4_5005_c](https://github.com/user-attachments/assets/b03ec4ae-8d34-4002-9fbe-d1f088ab8bfa)
![F56385AB-3832-4E41-B138-207CA3E976FC_4_5005_c](https://github.com/user-attachments/assets/2dbbb092-db73-4272-bd99-ed5c2fa72041)
![2ED03AE2-531A-4581-8860-E6B1000EA0B9_4_5005_c](https://github.com/user-attachments/assets/84b76fc7-c08c-4e01-b063-e08e697fb3cc)
![E3274865-C90A-4BAF-B2AB-36356FA20CA6_4_5005_c](https://github.com/user-attachments/assets/3c16b871-cb0d-474d-a71c-4ba95aba682f)
![8F7FCF4E-CDA4-4EF5-B547-EF82C5D27B51_4_5005_c](https://github.com/user-attachments/assets/3db5bd47-f7c2-4bdc-87fa-4c9857663136)


---------------------------------------------------------------------------
    
    
Ištestuoti Vector klasės metodai:

![43844A5A-1AAB-4DFC-8C87-CFF122949E24_4_5005_c](https://github.com/user-attachments/assets/58775fa6-c5a4-4c9e-8851-16457e49c5e8)
    

---------------------------------------------------------------------------


5 Vector klasės metodų pavyzdžiai:
//1
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

//2
    void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }

//3
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

//4
    void clear() {
        size_ = 0;
    }

//5
    void assign(T* first, T* last) {
        clear();
        size_t new_size = last - first;
        if (new_size > capacity_) {
            reallocate(new_size);
        }
        for (size_t i = 0; i < new_size; ++i) {
            data_[i] = *(first + i);
        }
        size_ = new_size;
    }






main.cpp:

Meniu su galimais pasirinkimais:

1 - Konstruktorius
![3B8CF75A-A5B2-4D6E-8972-0B1689468C1D_4_5005_c](https://github.com/user-attachments/assets/dbd6cc82-cbfc-49ea-a7f4-582cf5696087)

2 - Destruktorius

![520399B4-DE1D-4F24-814D-2F102A316E32_4_5005_c](https://github.com/user-attachments/assets/df130127-a27c-4d69-9233-fb02fb164072)

3 - Copy constructor
![E5852B52-8D07-47A8-8C68-A2CD3A1DC07E](https://github.com/user-attachments/assets/1a70ac2a-4a55-42ad-a1aa-c57cc08accca)

4 - Copy assignment operator
![5E9E2EE8-D570-4DE6-A52F-3591CDE9F8F3](https://github.com/user-attachments/assets/3ea4cbe6-4cb3-47b2-a501-415b22b1e411)

5 - Move constructor
![233046C4-CC8A-4522-AC35-6AD10C9D6535_4_5005_c](https://github.com/user-attachments/assets/d9c09ad9-8552-4180-9dfc-8da903cf4a13)

6 - Move operator
![CDBE1B1B-D4CF-4FD1-91C4-874FCFE67547](https://github.com/user-attachments/assets/26486863-5e90-493f-9c3a-8bfad9b1c13a)


7 - Input operator
![C190034C-EB0E-4129-9F7B-55F85A53F3EA_4_5005_c](https://github.com/user-attachments/assets/b6734531-06c4-47a2-a34c-653b5020d96a)


8 - Output operator
![0F9D68A4-E898-4AF9-9359-AE593093026D_4_5005_c](https://github.com/user-attachments/assets/4f092516-bef6-43d1-a042-1d0e76c8c949)

9 - studentų grupavimas ir išvedimas į failus

    9.1 - įvesti duomenis ranka
    
    9.2 - generuoti duomenis
    
    9.3 - nuskaityti duomenis iš failo







Kopiuterio parametrai:
CPU - Apple M3
RAM - 16 GB
SSD - 494,38 GB








