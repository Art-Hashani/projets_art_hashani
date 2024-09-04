public class Livre extends Document implements Empruntable {
    private String editeur;
    private boolean estDisponible;
    public Livre(String titre,String auteur,String editeur){
        super(titre,auteur);
        this.editeur=editeur;
    }
    public boolean estDisponible(){
        return this.estDisponible;
    }
    public void emprunter(){
        this.estDisponible=false;

    }
    public void rendre(){
        this.estDisponible=true;
    }
        
}


