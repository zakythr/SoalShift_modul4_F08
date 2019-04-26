# SoalShift_modul4_F08

##  SOAL 1

Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai: </br>
```qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0```

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka: </br>
<b>“INI_FOLDER/halo”</b> saat belum di-mount maka akan bernama <b>“n,nsbZ]wio/QBE#”</b>, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi <b>“INI_FOLDER/halo”</b> 

Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan


## SOAL 2

Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos”
Urutan operasi dari kebutuhan ini adalah:
<ol>
<li>  Tepat saat sebelum file system di-mount
    <ol>
    <li>Secara otomatis folder “Videos” terbuat di root directory file system
    <li>Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
    <li>Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
    <li>Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
    <li>Jangan tampilkan file pecahan di direktori manapun
  </ol>
  <li> Tepat saat file system akan di-unmount
    <ol>
    <li> Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
    <li> Hapus folder “Videos” 
    </ol>
    
