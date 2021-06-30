//adapun cara yang dilakukan untuk mentuning PID pada robot line follower ialah sebagai berikut:
//
//    Langkah awal gunakan kontrol proporsional terlebih dahulu, abaikan konstanta integratif dan derivatifnya dengan memberikan nilai nol pada integratif dan derivatif.
//    Tambahkan terus konstanta proporsional maksimum hingga keadaan stabil namun robot masih berosilasi.
//    Untuk meredam osilasi, tambahkan konstanta derivatif dengan membagi dua nilai proporsional, amati keadaan sistem robot hingga stabil dan lebih responsif.
//    Jika sistem robot telah stabil, kontrol integratif dapat menjadi opsional, dalam artian jika ingin mencoba-coba tambahkan kontrol integratif tersebut, namun pemberian nilai integratif yang tidak tepat dapat membuat sistem robot menjadi tidak stabil.
//    Nilai set point kecepatan dan nilai batas bawah/atas memberikan patokan kecepatan robot.
//    Nilai time sampling (waktu cuplik) juga mempengaruhi perhitungan PID, tentunnya saat penggunaan kontrol integratif dan derivatif.
//    Periksa kembali perfoma sistem hingga mendapatkan hasil yang memuaskan.



//coba sekarang udah mau belum buat belok
//oke mas, bentar takpsang bterainya
//udah mau belok,tpi blum pas, belok sedikit muter ditempat mas
//terllau tajem beloknya atau terlalu lambat
//kalau terlalau tajem ditambahin aja pembaginya yang (maxpwm/6) ditambah ke 7 ,8 atau berapa lah
//kalau terlalu lambat brrti dikurangin
//udah dulu mau lanjut kerjaan
//maaf ya
//oke mksih
