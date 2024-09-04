public class BandeDessinee extends Document{
    private String dessinateur;
    public BandeDessinee(String titre,String auteur,String dessinateur){
        super(titre, auteur);
        this.dessinateur=dessinateur;
    }
}
