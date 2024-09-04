abstract public class Document{
    private String titre;
    private String auteur;
    public Document(String titre, String auteur){
        this.titre=titre;
        this.auteur=auteur;
    }
    public String getTitre(){
        return this.titre;
    }
}
