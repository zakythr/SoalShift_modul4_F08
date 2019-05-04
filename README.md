# SoalShift_modul4_F08

##  SOAL 1

Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai: </br>
```qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0```

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka: </br>
<b>“INI_FOLDER/halo”</b> saat belum di-mount maka akan bernama <b>“n,nsbZ]wio/QBE#”</b>, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi <b>“INI_FOLDER/halo”</b> 

Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

- Langkah pertama, kita membuat fungsi encrypt dan decryptnya
```
void encrypt(char change[])
{
	int n, i, ch;
	for(n = 0; change[n] != '\0'; ++n)
	{
		ch = change[n];

		if(ch == '/') continue;		//jika bertemu / maka akan lanjut mengencrypt

		for(i = 0; i < strlen(cipher); i++)
		{
			if(ch == cipher[i]) break;
		}
		
		i = i + 17;
		if(i > 93) i = i - strlen(cipher);

		change[n] = cipher[i];
	}
}

void decrypt(char change[])
{
	int n, i, ch;
	for(n = 0; change[n] != '\0'; ++n)
	{
		ch = change[n];

		if(ch == '/') continue;

		for(i = 0; i < strlen(cipher); i++)
		{
			if(ch == cipher[i]) break;
		}
		
		i = i - 17;
		if(i < 0) i = i + strlen(cipher);

		change[n] = cipher[i];
	}
}

```
- Langkah kedua, memanggil fungsi encrypt pada xmp_read, xmp_getattr, dan xmp_readdir. Memanggil fungsi decrypt pada xmp_readdir

##  SOAL 3
Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:
Owner Name 	: ‘chipset’ atau ‘ic_controller’
Group Name	: ‘rusak’
Tidak dapat dibaca
Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

```
if( (strcmp(p->pw_name, "chipset") == 0 || strcmp(p->pw_name, "ic_controller") == 0) && strcmp(g->gr_name, "rusak") == 0 )
				{
					//check if file readable
					if(fopen(show, "r") == NULL)
					{
						//error access??
						if(errno == EACCES)
						{
							//it's time for record
							FILE *teks;
							int tahun = waktu->tm_year + 1900;
							char sumber[1000];
							char ketikan[2064];
							sprintf(sumber, "%s/V[EOr[c[Y`HDH", dirpath);	//encrypt an filemiris.txt
							sprintf(ketikan, "%s %d %d | waktu : %02d:%02d:%02d [%02d %02d %04d]\n", show, st.st_uid, st.st_gid, waktu->tm_hour, waktu->tm_min, waktu->tm_sec, waktu->tm_mday, waktu->tm_mon, tahun);
							teks = fopen(sumber, "a");	//membuka filemiris.txt, "a" membuat file jika blm dibuat
							fputs(ketikan, teks);		//meletakkan teks ke dlm file
							fclose(teks);			//menutup filemiris.txt

							remove(show);
						}
					}	

					//no.1
					else 
					{
						decrypt(dpath);
						res = (filler(buf, dpath, &st, 0));
						if(res!=0) break;
					}
				}

```

##  SOAL 4
Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

- Langkah pertama, kita membuat kondisijika di dalam folder YOUTUBER maka membuat folder permission nya 0750 dan membuat file dengan permission 0640 
```
    if(strstr(fpath, "/@ZA>AXio/") != NULL)	//hasil encrypt YOUTUBER
    {
    	res = mkdir(fpath, 0750);
    }
    else res = mkdir(fpath, mode); 
    
    if(strstr(fpath, "/@ZA>AXio/") != NULL)		//mencari string @ZA>AXio dalam string /@ZA>AXio/
    {							//return NULL jika tdk ada
    	res = creat(fpath, 0640);
    }
    else res = creat(fpath, mode);
```

- Lalu membuat pesan error jika, merubah permission file yang ber-ekstensi "iz1"

```
if(strcmp(ext, ".iz1")==0)
		{
			pid_t child;
			child = fork();

			if(child==0)
			{
				char *argv[4] = {"zenity", "--warning", "--text='File ekstensi iz1 tidak boleh diubah permissionnya.'", NULL};
				execv("/usr/bin/zenity", argv);
			}
			return 0;
		}
```

