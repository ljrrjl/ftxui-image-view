# An FTXUI component for displaying images  

## Preview

![](./doc/example.png)



## Dependencies 

+ [TerminalImageViewer](https://github.com/stefanhaustein/TerminalImageViewer.git): It's a magical library, and I've modified some of the source code to adapt it to FTXUI( See in `./libs` ). For users it's usually just a matter of installing **ImageMagick**, which on ubuntu you can pass:   

  ```shell
  sudo apt install imagemagick
  ```



## API

see `./example`

```c++
Element image_view(std::string_view path) { 
	return std::make_shared<ImageView>(path); 
} 
```
