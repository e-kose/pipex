## Giriş

Bu projede, shell'den bildiğimiz ve sevdiğimiz boru (``|``) işlemini kendi başımıza gerçekleştireceğiz. Bunun için, boru, fork ve dup gibi bir dizi yeni fonksiyon kullanarak çoklu süreçler kavramını tanıyacağız.

[TUTORIAL](https://en.wikipedia.org/wiki/Pipeline_(Unix))

## Pipex Shell'de

Bu projede, aşağıdaki shell komutunun davranışını taklit eden bir program kodlamamız isteniyor:

```shell
❯ < file1 cmd1 | cmd2 > file2
```
## Programın Amacı

Programın amacı, bir giriş dosyasını ve iki komutu alarak, bu dosyayı ilk komuta standart giriş (stdin) olarak vermek, ilk komutun çıktısını ikinci komuta boru (pipe) ile aktarmak ve son olarak sonucu ikinci dosyaya kaydetmektir. Komutları daha detaylı inceleyelim:

- ``<``: Bir sonraki argümanın standart giriş (stdin) olarak geçileceğini belirtir.
- ``file1``: Açmak istediğimiz dosyanın yolu. Okuma (read-only) modunda açılmalıdır ve mevcut olmalıdır.
- ``cmd1``: İlk komut. Giriş dosyasını alır ve uygun bir şekilde çalıştırır.
- ``|``: İlk komutun standart çıkış (stdout) verisini ikinci komutun standart giriş (stdin) olarak kullanır.
- ``cmd2``: İlk komutun çıktısını standart giriş olarak alır ve uygun bir şekilde çalıştırır.
- ``>``: Standart çıkış (stdout) verilerini bir dosyaya yönlendirir, dosya mevcut değilse oluşturur.
- ``file2``: Bir çıkış dosyasının yolu. Mevcutsa, dosya boşaltılır (truncated) ve yazma (write-only) modunda açılır.

## Pipex Algoritması

Yukarıdaki komutun kendi uygulamamız benzer bir şekilde görünecek. ``pipex`` adında bir çalıştırılabilir dosya derleyeceğiz. Bu program sadece dört zorunlu komutu kabul eder:

```shell
❯ ./pipex file1 cmd1 cmd2 file2
```

Bu projede, pipe, fork ve dup gibi yeni araçları kullanarak çalışacağız. İşte bu fonksiyonların kısa açıklamaları:

| Fonksiyon            | Açıklama                                                         | Dönen Değer                                    |
|----------------------|------------------------------------------------------------------|------------------------------------------------|
| ``pipe(fd)``         | ``fd[2]`` alır ve ``fd[0]``'ı okuma, ``fd[1]``'i yazma için açar | ``-1`` hata                                   |
| ``fork()``           | Süreci böler ve çocuk süreci ``0`` ile oluşturur                 | Her iki sürecin (çocuk = ``0``, ana > ``0``) işlem kimliği, ``-1`` hata |
| ``dup2(oldfd, newfd)``| ``newfd``'yi kapatır ve ``oldfd``'yi ``newfd``'ye kopyalar      | ``-1`` hata                                   |
| ``execve(path, cmd, envp)`` | Tam yolunu, NULL-termin edilmiş parametreler dizisini ve ortamı alır. Mevcut süreci belirtilen komut ile değiştirir | ``-1`` hata       |

İlk adımda, komutlar için yolları elde etmemiz gerekiyordu. Bunu, Unix tabanlı sistemlerde bulunan ``PATH`` değişkenine bakarak yaptık. Tam yol ve parametreler dizisini daha sonra erişim için bir bağlı liste (linked list) olarak sakladık.

Komutları sakladıktan sonra ve bazı titiz hata kontrollerinden sonra, komut listesi üzerinde bir ``while`` döngüsü ile döneriz. Her düğüm için yeni bir pipe ve fork oluştururuz. Bu pipe'ları çocuk süreçlerin yazma uçlarını ana süreçlerin okuma uçlarıyla bağlamak için kullanırız. ``dup2`` kullanarak giriş dosyasını standart girişe yönlendiririz ve sonunda çıkış dosyasına yönlendiririz. Çocuk süreçler ``fd[1]``'e yazar ve tüm gereksiz dosya tanımlayıcılarını dikkatlice kapatır. Her çocuk, bağlı listedeki mevcut komutları çalıştırır ve pipe, çıktıyı ana sürece gönderir. Ana süreç, çocuk sürecinin bitmesini bekler ve pipe'ın okuma ucunu bir sonraki komut için ``stdin``'e geri yönlendirir, kullanılmayan dosya tanımlayıcılarını kapatır.

Ana süreç tamamlandığında, komutların çıktıları çıkış dosyasına ulaşmış olmalıdır. Bu noktadan sonra, tüm ayrılmış belleği serbest bırakmak ve artık kullanılmayan dosya tanımlayıcılarını kapatmak için ``pipex_exit`` adında bir fonksiyon çağırabiliriz.

